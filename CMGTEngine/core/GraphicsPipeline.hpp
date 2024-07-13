#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include "glm.hpp"
#include<string>
#include<vector>
#include<list>
#include "VulkanInstance.hpp"
#include "VulkanDescriptor.hpp"
#include "VulkanRenderer.hpp"
using namespace std;

namespace cmgt {
	class Mesh;
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
		GraphicsPipeline(const GraphicsPipelineInfo& info, ShaderProgram* pShaderProgram);
		GraphicsPipeline(ShaderProgram* pShaderProgram);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);


		void createPipeline();
		void renderMeshes(const VulkanFrameData& frameData);
		void AddMeshToRender(Mesh* mesh);
		void RemoveFromRenderer(Mesh* mesh);
		void setPushConstants(VkCommandBuffer commandBuffer, const void* pData);
	private:

		void createPipeline(const GraphicsPipelineInfo& info);
		//MOVE TO SHADER PROGRAM

		//
		VkPipeline graphicsPipeline;
		ShaderProgram* shaderProgram;
		list<Mesh*> meshesToRender;
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_HPP