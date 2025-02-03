#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#pragma once
#include "minimal/paths.h"
#include<string>
#include<vector>
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanDescriptor.h"

namespace cmgt {
	class ShaderProgram {
		friend class GraphicsPipeline;
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, uint32_t pushSize, uint32_t uniformSize, VulkanInstance& instance); 
		virtual ~ShaderProgram();
		virtual void BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages);
		void writeUniformBuffers(const VulkanFrameData& frameData);
		void setupPushConsts(VkPushConstantRange& range);
		void setupUniformBuffers(VulkanDescriptorSetLayout& descriptorSetLayout);
		const uint32_t pushSize; const uint32_t uniformSize;
		const uint32_t stageNum = 2;
	protected:
		
		static std::vector<char> readFile(const std::string& filepath);
		void CreateShader(const std::string& shaderFile, VkShaderModule* module);
		void CreateShader(const std::vector<char>& shader, VkShaderModule* module);

		virtual void bindUniformBuffers(uint32_t imageindex, const void* pData);

		VulkanInstance& vkInstance;
		VulkanDescriptorPool descriptorPool;
		std::vector<VulkanBuffer*> uniformBuffers;
		std::vector<VkDescriptorSet> descriptorSets;
		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;

	};
}

#endif //SHADERPROGRAM_HPP