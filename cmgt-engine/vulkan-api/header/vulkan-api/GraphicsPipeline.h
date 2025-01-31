#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H

#pragma once
#include "minimal/paths.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "vulkan-api/VulkanFrameData.h"
#include<vector>
#include<list>
using namespace std;

namespace cmgt {
	class VulkanBuffer;
	class ShaderProgram;
	struct GraphicsPipelineInfo
	{
		GraphicsPipelineInfo() = default;
		GraphicsPipelineInfo(const GraphicsPipelineInfo&) = delete;
		GraphicsPipelineInfo& operator=(const GraphicsPipelineInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};


	class GraphicsPipeline {
	public:
		GraphicsPipeline(VulkanInstance& instance,const GraphicsPipelineInfo& info, ShaderProgram& pShaderProgram);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);

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
		ShaderProgram& shaderProgram;
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_H