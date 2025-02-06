
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/Window.h"
#include "core/GraphicsPipeline.h"
#include<array>
#include <stdexcept>
namespace cmgt {
	VulkanRenderer::VulkanRenderer() : Singelton<VulkanRenderer>(this) {
		createCommandBuffers();
	}
	VulkanRenderer::~VulkanRenderer() {
		for(GraphicsPipeline* pipeline : pipelines){
			delete pipeline;
		}
		pipelines.clear();
	}

	void VulkanRenderer::createCommandBuffers() {

		commandBuffers.resize(VulkanSwapchain::get()->imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = VulkanInstance::get()->getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(VulkanInstance::get()->device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void VulkanRenderer::freeCommandBuffers() {
		VulkanInstance* VkInstance = VulkanInstance::get();
		vkFreeCommandBuffers(VkInstance->device(), VkInstance->getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void VulkanRenderer::recordCommandBuffer(int imageIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

		VulkanSwapchain* VkSwapchain = VulkanSwapchain::get();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = VkSwapchain->getRenderPass();
		renderPassInfo.framebuffer = VkSwapchain->getFrameBuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0,0 };
		renderPassInfo.renderArea.extent = VkSwapchain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f,0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();
		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};

		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(VkSwapchain->width());
		viewport.height = static_cast<float>(VkSwapchain->height());
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, VkSwapchain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);
		
		
		VulkanFrameData frameData(commandBuffers[imageIndex],imageIndex, viewMatrix, projectionMatrix);

		//Good performance but explore the option for meshes to render themsleves
		//This way you don't have to keep track of which mesh is visible
		for(GraphicsPipeline* pipeline : pipelines){
			pipeline->recordFrameCommandBuffer(frameData);
		}
		
		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer!");
	}

	void VulkanRenderer::drawFrame(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
		VulkanSwapchain* VkSwapchain = VulkanSwapchain::get();
		uint32_t imageIndex;
		VkResult result = VkSwapchain->acquireNextImage(imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to accure swap chain image");

		recordCommandBuffer(imageIndex,viewMatrix,projectionMatrix);
		result = VkSwapchain->submitCommandBuffers(commandBuffers[imageIndex], imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || Window::get()->isWindowResized()) {
			Window::get()->resetWindowResizeFlag();
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chian image!");
	}

	void VulkanRenderer::recreateSwapchain() {
		Window* gameWindow = Window::get();
		auto extent = gameWindow->getWindowExtend();
		while (extent.width == 0 || extent.height == 0) {
			extent = gameWindow->getWindowExtend();
			
			Window::get()->waitEvents();
		}
		
		vkDeviceWaitIdle(VulkanInstance::get()->device());

		VulkanSwapchain* VkSwapchain = VulkanSwapchain::get();
		VkSwapchain->destroySwapchain();
		VkSwapchain->createSwapChain();
		if (VkSwapchain->imageCount() != commandBuffers.size()) {
			freeCommandBuffers();
			createCommandBuffers();
		}
		
		//OnSwapchainRecreate.trigger();
	}
}
