#include "Game.hpp"


namespace cmgt {
	Game::Game(int Width,int Height,string Name) {	
		gameWindow = new Window(Width, Height, Name);
	}

	Game::~Game() {

		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		vulkanAPI = new VulkanInstance(*gameWindow);
		vulkanSwapChian = new VulkanSwapchain(*vulkanAPI, gameWindow->getWindiwExtend());
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
		if (vkCreatePipelineLayout(vulkanAPI->device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw runtime_error("failed to create pipelin layout");
	}

	void Game::createPipeline() {
		auto pipelineConfig = ShaderProgram::defaultShaderProgramInfo(vulkanSwapChian->width(), vulkanSwapChian->height());
		pipelineConfig.renderPass = vulkanSwapChian->getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		shader = new ShaderProgram(*vulkanAPI, "vert.spv", "frag.spv", pipelineConfig);
	}

	void Game::createCommandBuffers() {
		commandBuffers.resize(vulkanSwapChian->imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = vulkanAPI->getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(vulkanAPI->device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw runtime_error("failed to allocate command buffers!");

		for (int i = 0; i < commandBuffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
				throw runtime_error("failed to begin recording command buffer!");

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = vulkanSwapChian->getRenderPass();
			renderPassInfo.framebuffer = vulkanSwapChian->getFrameBuffer(i);
			renderPassInfo.renderArea.offset = { 0,0 };
			renderPassInfo.renderArea.extent = vulkanSwapChian->getSwapChainExtent();

			array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
			clearValues[1].depthStencil = { 1.0f,0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();
			vkCmdBeginRenderPass(commandBuffers[i],&renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			shader->bind(commandBuffers[i]);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				throw runtime_error("failed to record command buffer!");
		}
	}

	void Game::drawFrame() {
		uint32_t imageIndex;
		VkResult result = vulkanSwapChian->acquireNextImage(&imageIndex);
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw runtime_error("failed to accure swap chain image");

		result = vulkanSwapChian->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
			throw runtime_error("failed to present swap chian image!");
	}

	void Game::run() {
		initEngine();
		OnInit();
		OnStart();
		while (!gameWindow->isOpened()) {
			gameWindow->update();
			OnUpdate();
			OnRender();
			drawFrame();
		}
		exit();
	}

	void Game::exit() {
		vkDeviceWaitIdle(vulkanAPI->device());
		OnExit();
		vkDestroyPipelineLayout(vulkanAPI->device(), pipelineLayout, nullptr);
		gameWindow->close();
		delete gameWindow;
		delete shader;
		delete vulkanSwapChian;
		delete vulkanAPI;
	}

}
