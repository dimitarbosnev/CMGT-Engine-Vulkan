#pragma once
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {

	ShaderProgram::ShaderProgram(const string& vertexFile, const string& fragmentFile,
		const string& tessellationControlFile, const string& tessellationEvaluationFile, const string& geometryFile) {
		cout << "Initalizing Shaders...\n";
		CreateShader(vertexFile, &vertexShaderModule);
		cout << "\t Vertex Shader Initalized!\n";
		CreateShader(fragmentFile, &fragmentShaderModule);
		cout << "\t Fragment Shader Initalized!\n";
		CreateShader(tessellationControlFile, &tessellationControlShaderModule);
		CreateShader(tessellationEvaluationFile, &tessellationEvaluationShaderModule);
		CreateShader(geometryFile, &geometryShaderModule);
		cout << "Shaders Initalized!\n";
	}

	ShaderProgram::~ShaderProgram() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		vkDestroyShaderModule(instance.device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(instance.device(), fragmentShaderModule, nullptr);
		cout << "Shader destroyed" << endl;
	}


	vector<char> ShaderProgram::readFile(const string& filename) {
		std::ifstream file(filename, ios::ate | ios::binary);

		if (!file.is_open()) {
			throw runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	void ShaderProgram::CreateShader(const string& shaderFile, VkShaderModule* module) {
		if (shaderFile == "") return;
		vector<char> shaderCode = readFile(paths::CMGT_SHADER_PATH + shaderFile);
		CreateShaderModule(shaderCode, module);
	}
	void ShaderProgram::CreatePipelineShaderStages(VkGraphicsPipelineCreateInfo& pipelineInfo)
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
	}


	void ShaderProgram::CreateShaderModule(const vector<char>& shader, VkShaderModule* module) {

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = shader.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.data());

		if (vkCreateShaderModule(VulkanInstance::getInstance().device(), &createInfo, nullptr, module) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}
}
