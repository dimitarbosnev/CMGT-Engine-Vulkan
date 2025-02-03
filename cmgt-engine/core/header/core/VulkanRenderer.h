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
			VulkanRenderer(VulkanInstance& instance, VulkanSwapchain& swapchian, Window& windnow);
			~VulkanRenderer();
			void recordCommandBuffer(int imageIndex);
			void drawFrame();

			
		private:
			VulkanInstance& vkInstance;
			VulkanSwapchain& vkSwapchian;
			Window& gameWindnow;
			//Event OnSwapchainRecreate;
			//Event OnCommandBufferRecord;
			std::vector<VkCommandBuffer> commandBuffers;
			void createCommandBuffers();
			void freeCommandBuffers();
			void recreateSwapchain();
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H