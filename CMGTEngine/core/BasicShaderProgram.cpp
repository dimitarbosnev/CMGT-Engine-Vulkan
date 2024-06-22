#pragma once
#include "BasicShaderProgram.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {

	BasicShaderProgram::BasicShaderProgram(const string& vertexFile, const string& fragmentFile) {
		cout << "Initalizing Shaders...\n";

		CreateShader(vertexFile, &vertexShaderModule);
		cout << "\t Vertex Shader Initalized!\n";
		CreateShader(fragmentFile, &fragmentShaderModule);
		cout << "\t Fragment Shader Initalized!\n";

		cout << "Shaders Initalized!\n";
	}

	BasicShaderProgram::~BasicShaderProgram() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		vkDestroyShaderModule(instance.device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(instance.device(), fragmentShaderModule, nullptr);
		cout << "Shader destroyed" << endl;
	}
	void BasicShaderProgram::BindPipelineShaderStages(VkGraphicsPipelineCreateInfo& pipelineInfo)
	{
		VkPipelineShaderStageCreateInfo shaderStages[2];

		shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStages[0].module = vertexShaderModule;
		shaderStages[0].pName = "main";
		shaderStages[0].flags = 0;
		shaderStages[0].pNext = nullptr;
		shaderStages[0].pSpecializationInfo = nullptr;

		shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStages[1].module = fragmentShaderModule;
		shaderStages[1].pName = "main";
		shaderStages[1].flags = 0;
		shaderStages[1].pNext = nullptr;
		shaderStages[1].pSpecializationInfo = nullptr;

		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
	}

	void BasicShaderProgram::creatPipelineLayout()
	{
		VkPushConstantRange range;
		range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range.offset = 0;
		range.size = sizeof(BasicShaderProgram::BasicPushConstData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &range;
		if (vkCreatePipelineLayout(VulkanInstance::getInstance().device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw runtime_error("failed to create pipelin layout");
	}
