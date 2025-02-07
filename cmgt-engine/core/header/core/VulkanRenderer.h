#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#pragma once
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/Window.h"
#include "minimal/glm.h"
#include "minimal/events.h"
#include "minimal/types.h"
#include<string>
#include<vector>
#include<list>
namespace cmgt {
	class GraphicsPipeline;

	class VulkanRenderer : public Singelton<VulkanRenderer>{
		public:
			VulkanRenderer();
			~VulkanRenderer();
			void recordCommandBuffer(uint8_t imageIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
			void drawFrame(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
			std::list<GraphicsPipeline*> pipelines;
			
		private:
			//Event OnSwapchainRecreate;
			std::vector<VkCommandBuffer> commandBuffers;
			void createCommandBuffers();
			void freeCommandBuffers();
			void recreateSwapchain();
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H