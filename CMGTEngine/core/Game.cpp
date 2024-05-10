#pragma once
#include "Game.hpp"

namespace cmgt {

	Game::Game(int pWidth,int pHeight,string pName) {
		Window::InitializeWindow(pWidth, pHeight, pName);
	}

	Game::~Game() {
		glfwTerminate();
		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		VulkanInstance::InitializeVulkan();
		VulkanSwapchain::InitializeSwapchain(Window::getInstance().getWindiwExtend());
		//Hard coded mesh
		vector<Mesh::Vertex> vertecies{ {{0.0f,-0.5f,0.0f}, {1,0,0}},
			{{0.5f,0.5f,0.0f}, {0,1,0}},
			{{-0.5f,0.5f,0.0f},{0,0,1}} };
		mesh = new Mesh(vertecies);
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
		cout << "CMGT Engine Initialized!\n";
	}

	void Game::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(VulkanInstance::getInstance().device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw runtime_error("failed to create pipelin layout");
	}

	void Game::createPipeline() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		auto pipelineConfig = ShaderProgram::defaultShaderProgramInfo(swapchian.width(), swapchian.height());
		pipelineConfig.renderPass = swapchian.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		shader = new ShaderProgram(VulkanInstance::getInstance(), "vert.spv", "frag.spv", pipelineConfig);
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

		for (int i = 0; i < commandBuffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
				throw runtime_error("failed to begin recording command buffer!");

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = swapchian.getRenderPass();
			renderPassInfo.framebuffer = swapchian.getFrameBuffer(i);
			renderPassInfo.renderArea.offset = { 0,0 };
			renderPassInfo.renderArea.extent = swapchian.getSwapChainExtent();

			array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
			clearValues[1].depthStencil = { 1.0f,0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();
			vkCmdBeginRenderPass(commandBuffers[i],&renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			shader->bind(commandBuffers[i]);
			mesh->bind(commandBuffers[i]);
			mesh->render(commandBuffers[i]);
			//vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				throw runtime_error("failed to record command buffer!");
		}
	}

	void Game::drawFrame() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		uint32_t imageIndex;
		VkResult result = swapchian.acquireNextImage(&imageIndex);
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw runtime_error("failed to accure swap chain image");

		result = swapchian.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
			throw runtime_error("failed to present swap chian image!");
	}

	void Game::run() {

		initEngine();
		OnInit();
		OnStart();
		while (!Window::getInstance().isOpened()) {
			OnUpdate();
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
		delete mesh;
		delete &window;
		delete shader;
		delete &swapchain;
		delete &instance;

		glfwTerminate();
		cout << "GLFW Terminated!\n";
	}

}
