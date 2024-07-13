#ifndef VULKANRENDERER_HPP
#define VULKANRENDERER_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include<list>
#include "VulkanInstance.hpp"
#include "VulkanSwapchain.hpp"
#include "Camera.hpp"
#include "VulkanDescriptor.hpp"
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
#endif //VULKANRENDERER_HPP