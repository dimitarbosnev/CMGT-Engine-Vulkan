#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#pragma once
#include<string>
#include<vector>
#include<list>
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "core/Window.h"
#include "minimal/glm.h"
#include "minimal/events.h"
namespace cmgt {
	class GraphicsPipeline;

	class VulkanRenderer {
		public:
			VulkanRenderer(VulkanSwapchain& swapchian,VulkanInstance& instance);
			~VulkanRenderer();

			
		private:

			Event OnSwapchainRecreate;
			Event OnCommandBufferRecord;
			std::vector<VkCommandBuffer> commandBuffers;
			void recordCommandBuffer(VulkanSwapchain& swapchian, int imageIndex);
			void createCommandBuffers(VulkanSwapchain& swapchian,VulkanInstance& instance);
			void freeCommandBuffers(VulkanInstance& instance);
			void drawFrame(Window& windnow, VulkanSwapchain& swapchain, VulkanInstance& instance);
			void recreateSwapchain(VulkanInstance& instance, Window& windnow, VulkanSwapchain& swapchain);
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H