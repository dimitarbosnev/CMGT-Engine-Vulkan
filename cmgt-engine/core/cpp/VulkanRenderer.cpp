
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "core/Window.h"
#include<array>
#include <stdexcept>
namespace cmgt {
	VulkanRenderer::VulkanRenderer(VulkanSwapchain& swapchian,VulkanInstance& instance) {
		createCommandBuffers(swapchian,instance);
	}
	VulkanRenderer::~VulkanRenderer() {
	}

	void VulkanRenderer::createCommandBuffers(VulkanSwapchain& swapchian,VulkanInstance& instance) {

		commandBuffers.resize(swapchian.imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = instance.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(instance.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void VulkanRenderer::freeCommandBuffers(VulkanInstance& instance) {
		vkFreeCommandBuffers(instance.device(), instance.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void VulkanRenderer::recordCommandBuffer(VulkanSwapchain& swapchian, int imageIndex) {
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = swapchian.getRenderPass();
		renderPassInfo.framebuffer = swapchian.getFrameBuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0,0 };
		renderPassInfo.renderArea.extent = swapchian.getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f,0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();
		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};

		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapchian.width());
		viewport.height = static_cast<float>(swapchian.height());
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, swapchian.getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		OnCommandBufferRecord.trigger();
		//Camera& camera = *SceneManager::get().getCurrentScene()->getWorld().getMainCamera();
		//glm::mat4 viewMatrix = camera.getTransform();
		//glm::mat4 projectionMatrix = camera.getProjection();
		//VulkanFrameData frameData(commandBuffers[imageIndex],imageIndex, viewMatrix, projectionMatrix);
		//for (GraphicsPipeline* pipeline : pipelines)
		//	pipeline->renderMeshes(frameData);
		


		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer!");
	}

	void VulkanRenderer::drawFrame(Window& window, VulkanSwapchain& swapchain,  VulkanInstance& instance) {
		uint32_t imageIndex;
		VkResult result = swapchain.acquireNextImage(instance, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain(instance,window,swapchain);
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to accure swap chain image");

		recordCommandBuffer(swapchain, imageIndex);
		result = swapchain.submitCommandBuffers(instance, &commandBuffers[imageIndex], &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window.isWindowResized()) {
			window.resetWindowResizeFlag();
			recreateSwapchain(instance,window,swapchain);
			return;
		}
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chian image!");
	}

	void VulkanRenderer::recreateSwapchain(VulkanInstance& instance, Window& window, VulkanSwapchain& swapchain) {
		auto extent = window.getWindowExtend();
		while (extent.width == 0 || extent.height == 0) {
			extent = window.getWindowExtend();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(instance.device());

		swapchain.destroySwapchain(instance);
		swapchain.createSwapChain(instance);
		if (swapchain.imageCount() != commandBuffers.size()) {
			freeCommandBuffers(instance);
			createCommandBuffers(swapchain, instance);
		}
		
		OnSwapchainRecreate.trigger();
	}
}
