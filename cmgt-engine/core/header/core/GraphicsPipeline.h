#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H

#pragma once
#include "core/paths.h"
#include "core/config.h"
#include "core/glm.h"
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanDescriptor.h"
#include "render-engine/VulkanRenderer.h"
#include<vector>
#include<list>
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

#endif //GRAPHICSPIPELINE_H