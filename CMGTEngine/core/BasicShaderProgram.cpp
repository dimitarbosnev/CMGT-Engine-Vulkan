#pragma once
#include "BasicShaderProgram.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
#include<array>
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
	void BasicShaderProgram::BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages)
	{
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
	}
	int BasicShaderProgram::stageSize()
	{
		return 2;
	}
}
