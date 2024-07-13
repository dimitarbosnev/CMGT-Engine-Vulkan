#pragma once
#include "VulkanRenderer.hpp"
#include "SceneManager.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanBuffer.hpp"
#include "GraphicsPipeline.hpp"
#include "Scene.hpp"
#include<array>
namespace cmgt {
	void VulkanRenderer::InitializeRenderer() {
		assignInstance(new VulkanRenderer());
	}
	VulkanRenderer::VulkanRenderer() {
		createCommandBuffers();
	}
	VulkanRenderer::~VulkanRenderer() {
		for (GraphicsPipeline* pipeline : pipelines)
			delete pipeline;
		pipelines.clear();
		freeCommandBuffers();
	}
	void VulkanRenderer::AddGraphicsPipelines(GraphicsPipeline* pPipeline)
	{
		getInstance().pipelines.push_back(pPipeline);
	}

	void VulkanRenderer::render()
	{
		getInstance().drawFrame();
	}

	void VulkanRenderer::createCommandBuffers() {
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

	void VulkanRenderer::freeCommandBuffers() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		vkFreeCommandBuffers(instance.device(), instance.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void VulkanRenderer::recordCommandBuffer(int imageIndex) {
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


		Camera& camera = *SceneManager::getCurrentScene().getWorld().getMainCamera();
		glm::mat4 viewMatrix = camera.getTransform();
		glm::mat4 projectionMatrix = camera.getProjection();
		VulkanFrameData frameData(commandBuffers[imageIndex],imageIndex, viewMatrix, projectionMatrix);
		for (GraphicsPipeline* pipeline : pipelines)
			pipeline->renderMeshes(frameData);
		


		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			throw runtime_error("failed to record command buffer!");
	}

	void VulkanRenderer::drawFrame() {
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

	void VulkanRenderer::recreateSwapchain() {
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
		for (GraphicsPipeline* pipeline : pipelines)
			pipeline->createPipeline();
	}
}
