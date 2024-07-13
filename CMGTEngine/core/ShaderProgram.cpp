#pragma once
#include "ShaderProgram.hpp"
#include "VulkanInstance.hpp"
#include "VulkanBuffer.hpp"
#include "VulkanDescriptor.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {
	ShaderProgram::ShaderProgram() : 
		descriptorPool(VulkanDescriptorPool::Builder().setMaxSets(MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_FRAMES_IN_FLIGHT).build()) {
	}
	ShaderProgram::~ShaderProgram()
	{
		for (VulkanBuffer* buffer : uniformBuffers)
			delete buffer;
		uniformBuffers.clear();
		vkDestroyPipelineLayout(VulkanInstance::getInstance().device(), pipelineLayout, nullptr);
	}
	void ShaderProgram::setUniformBuffers(const VulkanFrameData& frameData)
	{
		bindUniformBuffers(frameData);

		vkCmdBindDescriptorSets(frameData.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[frameData.imageIndex], 0, nullptr);
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

	void ShaderProgram::setPushConstants(VkCommandBuffer commandBuffer, const void* pData)
	{
		vkCmdPushConstants(commandBuffer, pipelineLayout,
			VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			0, pushConstSize(), pData);
	}
	const VkPipelineLayout& ShaderProgram::getPipelineLayout() const
	{
		return pipelineLayout;
	}
}
