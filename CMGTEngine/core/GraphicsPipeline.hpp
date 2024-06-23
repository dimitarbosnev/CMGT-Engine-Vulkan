#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include<list>
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
		GraphicsPipeline(const GraphicsPipelineInfo& info, ShaderProgram* pShaderProgram);
		GraphicsPipeline(ShaderProgram* pShaderProgram);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);

		void setPushConstants(VkCommandBuffer commandBuffer, const void* pData);
		void createPipeline();

		inline static list<GraphicsPipeline*> pipelines = {};
	private:
		void creatPipelineLayout();
		void createPipeline(const GraphicsPipelineInfo& info);
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
		ShaderProgram* shaderProgram;

		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_HPP