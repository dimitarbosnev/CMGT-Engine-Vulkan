#pragma once
#include "GraphicsPipeline.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {

	GraphicsPipeline::GraphicsPipeline( const string& vertexFile,
		const string& fragmentFile, const GraphicsPipelineInfo& info) : shaderProgram(vertexFile, fragmentFile){
		CreateGraphicsPipeline(vertexFile, fragmentFile, info);
	}

	GraphicsPipeline::~GraphicsPipeline() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		vkDestroyPipeline(instance.device(), graphicsPipeline, nullptr);
		cout << "Pipeline destroyed" << endl;
	}


	void GraphicsPipeline::CreateGraphicsPipeline(const GraphicsPipelineInfo& configInfo) {

		auto bindingDescriptions = Mesh::Vertex::getBindingDescription();
		auto atttributeDescriptions = Mesh::Vertex::getAttributeDescription();
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(atttributeDescriptions.size());
		vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
		vertexInputInfo.pVertexAttributeDescriptions = atttributeDescriptions.data();
		vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

		VkPipelineShaderStageCreateInfo shaderStages[2];
		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
		pipelineInfo.pViewportState = &configInfo.viewportInfo;
		pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
		pipelineInfo.pMultisampleState = &configInfo.multisampleInfo;
		pipelineInfo.pColorBlendState = &configInfo.colorBlendInfo;
		pipelineInfo.pDepthStencilState = &configInfo.depthStencilInfo;
		pipelineInfo.pDynamicState = &configInfo.dynamicStateInfo;

		pipelineInfo.layout = configInfo.pipelineLayout;
		pipelineInfo.renderPass = configInfo.renderPass;
		pipelineInfo.subpass = configInfo.subpass;

		pipelineInfo.basePipelineIndex = -1;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(VulkanInstance::getInstance().device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
			throw runtime_error("failed to create pipeline");

		cout << "Shader Program Initalized!\n";
	}

	void GraphicsPipeline::bind(VkCommandBuffer commandBuffer) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,graphicsPipeline);
	}
}
