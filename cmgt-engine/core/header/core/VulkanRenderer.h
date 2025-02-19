#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#pragma once
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/Window.h"
#include "minimal/glm.h"
#include "minimal/events.h"
#include "minimal/types.h"
#include<string>
#include<vector>
#include<list>

#define MAX_AMOUT_LIGHTS 100
namespace cmgt {
	typedef std::array<LightStruct,100> Lights;
	class GraphicsPipeline;
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
			VkDescriptorSetLayout getDescriptorSetLayout(){ return GlobalDescriptorSetLayout.getDescriptorSetLayout(); }
			std::list<GraphicsPipeline*> pipelines;
			std::vector<LightStruct> lights;
			private:
			std::vector<size_t> sizes{ sizeof(GlobalUniformData), sizeof(LightStruct)*MAX_AMOUT_LIGHTS};
			std::unordered_map<uint32_t,VulkanBuffer*> GlobalDescriptorBuffers;
			std::vector<VkDescriptorSet> GlobalDescriptorSets;
			VulkanDescriptorSetLayout GlobalDescriptorSetLayout;
			VulkanDescriptorPool* GlobalDescriptorPool;
			std::vector<VkCommandBuffer> commandBuffers;
			void createCommandBuffers();
			void createDescriptorSets();
			void freeCommandBuffers();
			void recreateSwapchain();
			void writeDescriptorBuffers(const VulkanFrameData& frameData);
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H