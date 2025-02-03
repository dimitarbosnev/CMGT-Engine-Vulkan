
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/Window.h"
#include<array>
#include <stdexcept>
namespace cmgt {
	VulkanRenderer::VulkanRenderer(VulkanInstance& instance, VulkanSwapchain& swapchian, Window& windnow) : vkInstance(instance), vkSwapchian(swapchian), gameWindnow(windnow) {
		createCommandBuffers();
	}
	VulkanRenderer::~VulkanRenderer() {
	}

	void VulkanRenderer::createCommandBuffers() {

		commandBuffers.resize(vkSwapchian.imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = vkInstance.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(vkInstance.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void VulkanRenderer::freeCommandBuffers() {
		vkFreeCommandBuffers(vkInstance.device(), vkInstance.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void VulkanRenderer::recordCommandBuffer(int imageIndex) {
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = vkSwapchian.getRenderPass();
		renderPassInfo.framebuffer = vkSwapchian.getFrameBuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0,0 };
		renderPassInfo.renderArea.extent = vkSwapchian.getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f,0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();
		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};

		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(vkSwapchian.width());
		viewport.height = static_cast<float>(vkSwapchian.height());
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, vkSwapchian.getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		//OnCommandBufferRecord.trigger();

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

	void VulkanRenderer::drawFrame() {
		uint32_t imageIndex;
		VkResult result = vkSwapchian.acquireNextImage(imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to accure swap chain image");

		recordCommandBuffer(imageIndex);
		result = vkSwapchian.submitCommandBuffers(commandBuffers[imageIndex], imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || gameWindnow.isWindowResized()) {
			gameWindnow.resetWindowResizeFlag();
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chian image!");
	}

	void VulkanRenderer::recreateSwapchain() {
		auto extent = gameWindnow.getWindowExtend();
		while (extent.width == 0 || extent.height == 0) {
			extent = gameWindnow.getWindowExtend();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(vkInstance.device());

		vkSwapchian.destroySwapchain();
		vkSwapchian.createSwapChain();
		if (vkSwapchian.imageCount() != commandBuffers.size()) {
			freeCommandBuffers();
			createCommandBuffers();
		}
		
		//OnSwapchainRecreate.trigger();
	}
}
