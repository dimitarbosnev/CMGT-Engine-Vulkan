#pragma once
#include "ShaderProgram.hpp"
#include "VulkanInstance.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {
	ShaderProgram::~ShaderProgram()
	{
		
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
		vector<char> shaderCode = readFile(CMGT_SHADER_PATH + shaderFile);
		CreateShader(shaderCode, module);
	}

	void ShaderProgram::CreateShader(const vector<char>& shader, VkShaderModule* module) {

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = shader.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.data());

		if (vkCreateShaderModule(VulkanInstance::getInstance().device(), &createInfo, nullptr, module) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}
}
