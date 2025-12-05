#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#pragma once
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanUniformObject.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/Window.h"
#include "minimal/glm.h"
#include "minimal/events.h"
#include "minimal/types.h"
#include<string>
#include<vector>
#include<list>
#include<array>

#define MAX_AMOUT_LIGHTS 100
namespace cmgt {
	class GraphicsPipeline;
	class Object;
	class VulkanRenderer : public Singelton<VulkanRenderer>{
		public:
		struct GlobalUniformData {
			glm::mat4 cameraMatrix;
			glm::mat4 projMatrix;
			uint32_t lightCount;
		};
			VulkanRenderer();
			~VulkanRenderer();
			void recordCommandBuffer(uint8_t imageIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
			void drawFrame(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
			VkDescriptorSetLayout getDescriptorSetLayout(){ return GlobalUniformSets.getLayout(); }
			void scheduleLight(LightStruct light);
			void scheduleForRender(GraphicsPipeline* pipeline, Object* obj);
			private:

			std::map<GraphicsPipeline*, std::vector<Object*>> pipelines;
			std::vector<LightStruct> lights;
			VulkanUniformObject GlobalUniformSets;

			std::vector<VkCommandBuffer> commandBuffers;
			void createCommandBuffers();
			void freeCommandBuffers();
			void recreateSwapchain();
			void writeDescriptorBuffers(const VulkanFrameData& frameData);
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H