#pragma once
#include "BasicShaderProgram.hpp"
#include "Mesh.hpp"
#include <fstream>
#include<stdexcept>
#include<iostream>
#include<array>
namespace cmgt {

	BasicShaderProgram::BasicShaderProgram(const string& vertexFile, const string& fragmentFile) : ShaderProgram() {
		cout << "Initalizing Shaders...\n";

		CreateShader(vertexFile, &vertexShaderModule);
		cout << "\t Vertex Shader Initalized!\n";
		CreateShader(fragmentFile, &fragmentShaderModule);
		cout << "\t Fragment Shader Initalized!\n";

		cout << "Shaders Initalized!\n";
		createPipelineLayout();
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

	void BasicShaderProgram::createPipelineLayout() {
		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			VulkanBuffer* buffer = new VulkanBuffer(uniformSize(), 1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
			uniformBuffers.push_back(buffer);
			buffer->map();
		}
		VulkanDescriptorSetLayout descriptorSetLayout = VulkanDescriptorSetLayout::Builder()
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT).build();


		descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {
			VkDescriptorBufferInfo bufferInfo = uniformBuffers[i]->descriptorInfo();
			VulkanDescriptorWriter(descriptorSetLayout, descriptorPool).writeBuffer(0, &bufferInfo).build(descriptorSets[i]);
		}

		VkPushConstantRange range;
		range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range.offset = 0;
		range.size = pushConstSize();

		vector<VkDescriptorSetLayout> descriptorSetLayouts{ descriptorSetLayout.getDescriptorSetLayout() };
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &range;
		if (vkCreatePipelineLayout(VulkanInstance::getInstance().device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw runtime_error("failed to create pipelin layout");
	}

	int BasicShaderProgram::stageSize()
	{
		return 2;
	}
	void BasicShaderProgram::bindUniformBuffers(const VulkanFrameData& frameData)
	{
		UniformData uniformData;
		uniformData.cameraMatrix = frameData.viewMatrix;
		uniformData.projMatrix = frameData.projectionMatrix;
		uniformData.dirLight = glm::vec4(glm::normalize(glm::vec3(1, -1, 1)), 1);
		uniformData.ambientLight = glm::vec4(1, 1, 1, .2f);
		uniformBuffers[frameData.imageIndex]->writeToBuffer(&uniformData);
		uniformBuffers[frameData.imageIndex]->flush();
	}
	uint32_t BasicShaderProgram::pushConstSize()
	{
		return sizeof(BasicPushConstData);
	}
	uint32_t BasicShaderProgram::uniformSize()
	{
		return sizeof(UniformData);
	}
}
