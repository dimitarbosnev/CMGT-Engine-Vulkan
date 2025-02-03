#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H

#pragma once
#include "minimal/paths.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/ShaderProgram.h"
#include<vector>
#include<list>

namespace cmgt {
	struct GraphicsPipelineInfo
	{
		GraphicsPipelineInfo() = default;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		uint32_t subpass = 0;
	};


	class GraphicsPipeline {
	public:
		GraphicsPipeline(const GraphicsPipelineInfo& info, ShaderProgram pShaderProgram, VulkanSwapchain& swapchain);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);
		static GraphicsPipelineInfo defaultGraphicsPipelineInfo();
		void writePushConstants(VkCommandBuffer commandBuffer, const void* pData);
		void writeUniformBuffers(const VulkanFrameData& frameData,  const void* pData);
		void createPipeline();
	private:

		void createPipeline(const GraphicsPipelineInfo& info);
		void createPipelineLayout();
		//MOVE TO SHADER PROGRAM

		//
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
		VulkanInstance& vkInstance;
		VulkanSwapchain& vkSwapchain;
		ShaderProgram shaderProgram;
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_H