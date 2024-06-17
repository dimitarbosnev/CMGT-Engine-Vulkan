#pragma once
#include "Game.hpp"
#include "glm.hpp"
#include "Camera.hpp"
#include "VulkanRenderer.hpp"
#include "Scene.hpp"
namespace cmgt {

	Game::Game(int pWidth, int pHeight, string pName) {
		Window::InitializeWindow(pWidth, pHeight, pName);
	}

	Game::~Game() {
		glfwTerminate();
		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		VulkanInstance::InitializeVulkan();
		VulkanSwapchain::InitializeSwapchain(Window::getInstance().getWindowExtend());
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
		cout << "Initalizing CMGT Engine Utils...\n";
			ObjectManager::InitializesObjectManager();
			SceneManager::InitializesSceneManager();
			VulkanRenderer::InitializeRenderer();
		cout << "Utils Initalized!\n";

		cout << "CMGT Engine Initialized!\n";
	}

	void Game::createPipelineLayout() {
		VkPushConstantRange range;
		range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range.offset = 0;
		range.size = sizeof(PushConstantData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &range;
		if (vkCreatePipelineLayout(VulkanInstance::getInstance().device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw runtime_error("failed to create pipelin layout");
	}

	void Game::createPipeline() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		ShaderProgramInfo pipelineConfig{};
		ShaderProgram::defaultShaderProgramInfo(pipelineConfig);
		pipelineConfig.renderPass = swapchian.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		if (shader != nullptr)
			delete shader;
		shader = nullptr;
		shader = new ShaderProgram(VulkanInstance::getInstance(), "vert.spv", "frag.spv", pipelineConfig);
	}

	void Game::recreateSwapchain() {
		Window& window = Window::getInstance();
		auto extent = window.getWindowExtend();
		while (extent.width == 0 || extent.height == 0) {
			extent = window.getWindowExtend();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(VulkanInstance::getInstance().device());


		VulkanSwapchain::RecreateSwapchain(extent);
		if (VulkanSwapchain::getInstance().imageCount() != commandBuffers.size()) {
			freeCommandBuffers();
			createCommandBuffers();
		}
		createPipeline();
	}

	void Game::createCommandBuffers() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		VulkanInstance& instance = VulkanInstance::getInstance();
		commandBuffers.resize(swapchian.imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = instance.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(instance.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw runtime_error("failed to allocate command buffers!");
	}

	void Game::freeCommandBuffers() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		vkFreeCommandBuffers(instance.device(), instance.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void Game::recordCommandBuffer(int imageIndex) {
		VulkanSwapchain& swapchain = VulkanSwapchain::getInstance();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			throw runtime_error("failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = swapchain.getRenderPass();
		renderPassInfo.framebuffer = swapchain.getFrameBuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0,0 };
		renderPassInfo.renderArea.extent = swapchain.getSwapChainExtent();

		array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f,0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();
		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};

		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapchain.width());
		viewport.height = static_cast<float>(swapchain.height());
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, swapchain.getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);


		shader->bind(commandBuffers[imageIndex]);
		for (Mesh* mesh : VulkanRenderer::getInstance().meshesToRender) {
			mesh->bind(commandBuffers[imageIndex]);
		}


		for (Mesh* mesh : VulkanRenderer::getInstance().meshesToRender) {
			PushConstantData data;
			Camera& camera = *SceneManager::getCurrentScene().getWorld().getMainCamera();
			data.mvpMatrix = camera.getProjection() * camera.getTransform() * mesh->getTransform();
			data.time = (float)glfwGetTime();
			vkCmdPushConstants(commandBuffers[imageIndex], pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0, sizeof(PushConstantData), &data);
			mesh->render(commandBuffers[imageIndex]);
		}
		

		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			throw runtime_error("failed to record command buffer!");
	}

	void Game::drawFrame() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		uint32_t imageIndex;
		VkResult result = swapchian.acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw runtime_error("failed to accure swap chain image");

		recordCommandBuffer(imageIndex);
		result = swapchian.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || Window::getInstance().isWindowResized()) {
			Window::getInstance().resetWindowResizeFlag();
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS)
			throw runtime_error("failed to present swap chian image!");
	}


	void Game::run() {

		initEngine();
		OnInit();
		OnStart();
		float lastTick = glfwGetTime();
		while (!Window::getInstance().isOpened()) {
			double time = glfwGetTime();
			_deltaTime = (float)time - lastTick;
			lastTick = (float)time;
			OnUpdate();
			SceneManager::update(_deltaTime);
			OnRender();
			drawFrame();
		}
		exit();
	}

	void Game::exit() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		Window& window = Window::getInstance();
		VulkanSwapchain& swapchain = VulkanSwapchain::getInstance();
		vkDeviceWaitIdle(instance.device());
		OnExit();
		vkDestroyPipelineLayout(instance.device(), pipelineLayout, nullptr);
		//delete mesh;
		delete shader;
		SceneManager::destroyInstance();
		ObjectManager::destroyInstance();
		Window::destroyInstance();
		VulkanRenderer::destroyInstance();
		VulkanSwapchain::destroyInstance();
		VulkanInstance::destroyInstance();

		glfwTerminate();
		cout << "GLFW Terminated!\n";
	}

}
