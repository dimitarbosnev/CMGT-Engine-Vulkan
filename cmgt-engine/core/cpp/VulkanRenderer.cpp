
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/Window.h"
#include "core/GraphicsPipeline.h"
#include "minimal/log.h"
#include<array>
#include <stdexcept>

namespace cmgt {
	VulkanRenderer::VulkanRenderer() : Singelton<VulkanRenderer>(this), GlobalUniformSets(VulkanUniformObject::Builder()
	.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(GlobalUniformData))	
	.addBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(LightStruct) * MAX_AMOUT_LIGHTS),VulkanInstance::get())
	{
		lights.reserve(MAX_AMOUT_LIGHTS);
		createCommandBuffers();
		//createDescriptorSets();
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

	void VulkanRenderer::writeDescriptorBuffers(const VulkanFrameData& frameData){

		GlobalUniformData uniformData;
		uniformData.cameraMatrix = frameData.viewMatrix;
		uniformData.projMatrix = frameData.projectionMatrix;
		uniformData.lightCount = lights.size();

		GlobalUniformSets.getBufferAt(0)->writeToIndex(&uniformData, frameData.imageIndex);
		GlobalUniformSets.getBufferAt(1)->writeToIndex(lights.data(), frameData.imageIndex);
		std::stringstream ss;
		ss <<" Number of lights: " << lights.size();
		Log::msg(ss.str());
	}

	void VulkanRenderer::freeCommandBuffers() {
		VulkanInstance* VkInstance = VulkanInstance::get();
		vkFreeCommandBuffers(VkInstance->device(), VkInstance->getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void VulkanRenderer::recordCommandBuffer(uint8_t imageIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

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

		writeDescriptorBuffers(frameData);
		for(GraphicsPipeline* pipeline : pipelines){
			pipeline->bind(frameData.commandBuffer);
			vkCmdBindDescriptorSets(frameData.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipelineLayout(), 0, 1, &GlobalUniformSets.getDescriptorSet(frameData.imageIndex), 0, nullptr);
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
		
		lights.clear();
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
		VkSwapchain->recreateSwapChain();
		if (VkSwapchain->imageCount() != commandBuffers.size()) {
			freeCommandBuffers();
			createCommandBuffers();
		}
		
		//OnSwapchainRecreate.trigger();
	}

	void VulkanRenderer::scheduleLight(LightStruct light){
		if(lights.size() < MAX_AMOUT_LIGHTS)
			lights.push_back(light);
		else
			Log::warning("Reached the maximum amount of lights. This light will not be scheduled for render");
	}
}
