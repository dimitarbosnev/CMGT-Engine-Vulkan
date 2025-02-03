
#include "vulkan-api/ShaderProgram.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/VulkanDescriptor.h"
#include <filesystem>
#include <fstream>
#include<stdexcept>
#include<iostream>
namespace cmgt {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, uint32_t pPushSize, uint32_t pUniformSize, VulkanInstance& instance) : 
		descriptorPool(VulkanDescriptorPool::Builder().setMaxSets(MAX_FRAMES_IN_FLIGHT).addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_FRAMES_IN_FLIGHT).build(instance)),
		 vkInstance(instance), pushSize(pPushSize), uniformSize(pUniformSize)  {
		std::cout << "Initalizing Shaders...\n";

		CreateShader(vertexShader, &vertexShaderModule);
		std::cout << "\t Vertex Shader Initalized!\n";
		CreateShader(fragmentShader, &fragmentShaderModule);
		std::cout << "\t Fragment Shader Initalized!\n";
	}
	ShaderProgram::~ShaderProgram()
	{
		vkDestroyShaderModule(vkInstance.device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(vkInstance.device(), fragmentShaderModule, nullptr);
		for (VulkanBuffer* buffer : uniformBuffers)
			delete buffer;
		uniformBuffers.clear();
		std::cout << "Shader destroyed" << std::endl;
	}

	std::vector<char> ShaderProgram::readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		std::filesystem::path syspath = std::filesystem::canonical(std::filesystem::current_path());
		std::cout<<syspath<<filename<<std::endl;
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	void ShaderProgram::CreateShader(const std::string& shaderFile, VkShaderModule* module) {
		std::vector<char> shaderCode = readFile(CMGT_SHADER_PATH + shaderFile);
		CreateShader(shaderCode, module);
	}

	void ShaderProgram::CreateShader(const std::vector<char>& shader, VkShaderModule* module) {

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = shader.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.data());

		if (vkCreateShaderModule(vkInstance.device(), &createInfo, nullptr, module) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}

	void ShaderProgram::setupPushConsts(VkPushConstantRange& range)
	{
		range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range.offset = 0;
		range.size = pushSize;
	}
	void ShaderProgram::setupUniformBuffers(VulkanDescriptorSetLayout& descriptorSetLayout){

		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VulkanBuffer* buffer = new VulkanBuffer(vkInstance,uniformSize, 1,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
			uniformBuffers.push_back(buffer);
			buffer->map();
		}

		descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {
			VkDescriptorBufferInfo bufferInfo = uniformBuffers[i]->descriptorInfo();
			VulkanDescriptorWriter(descriptorSetLayout, descriptorPool).writeBuffer(0, &bufferInfo).build(descriptorSets[i]);
		}
	}


	void ShaderProgram::BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages)
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

	

	void ShaderProgram::bindUniformBuffers(uint32_t imageIndex, const void* pData)
	{
		uniformBuffers[imageIndex]->writeToBuffer(pData);
		uniformBuffers[imageIndex]->flush();
	}
}
