#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#pragma once
#include<string>
#include<vector>
#include<list>
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanSwapchain.h"
#include "render-engine/VulkanDescriptor.h"
#include "core/glm.h"
using namespace std;

namespace cmgt {
	class GraphicsPipeline;
	struct VulkanFrameData {
	public:
		VulkanFrameData(const VkCommandBuffer& pCommandBuffer, const short& pImageIndex, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
			: commandBuffer(pCommandBuffer), imageIndex(pImageIndex), viewMatrix(pViewMatrix), projectionMatrix(pProjectionMatrix) {}
		const VkCommandBuffer& commandBuffer;
		const short& imageIndex;
		const glm::mat4& viewMatrix;
		const glm::mat4& projectionMatrix;

	};
	class VulkanRenderer : public Singleton<VulkanRenderer> {
		public:
			static void InitializeRenderer();
			~VulkanRenderer();



			static void AddGraphicsPipelines(GraphicsPipeline* pPipeline);
			static void render();
		protected:
			
		private:
			VulkanRenderer();
			vector<VkCommandBuffer> commandBuffers;
			void recordCommandBuffer(int imageIndex);
			void createCommandBuffers();
			void freeCommandBuffers();
			void drawFrame();
			void recreateSwapchain();
			list<GraphicsPipeline*> pipelines = {};
			VulkanRenderer(const VulkanRenderer&);
			VulkanRenderer& operator=(const VulkanRenderer&);
	};
}
#endif //VULKANRENDERER_H