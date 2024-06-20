#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
#include "ShaderProgram.hpp"
using namespace std;

namespace cmgt {
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
		GraphicsPipeline(const string& vertexFile, const string& fragmentFile, const GraphicsPipelineInfo& info);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);
	private:

		void CreateGraphicsPipeline(const string& vertexFile, const string& fragmentFile, const GraphicsPipelineInfo& info);
		VkPipeline graphicsPipeline;
		ShaderProgram shaderProgram;

		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_HPP