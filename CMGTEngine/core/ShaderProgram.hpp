#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanRenderer.hpp"
#include "VulkanBuffer.hpp"
using namespace std;

namespace cmgt {
	class ShaderProgram {
	public:
		ShaderProgram(); 
		virtual ~ShaderProgram();
		virtual void BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages) = 0;
		void setUniformBuffers(const VulkanFrameData& frameData);

		virtual int stageSize() = 0;
		void setPushConstants(VkCommandBuffer commandBuffer, const void* pData);
		const VkPipelineLayout& getPipelineLayout() const;
	protected:
		
		static vector<char> readFile(const string& filepath);
		void CreateShader(const string& shaderFile, VkShaderModule* module);
		void CreateShader(const vector<char>& shader, VkShaderModule* module);
		virtual void createPipelineLayout() = 0;
		virtual void bindUniformBuffers(const VulkanFrameData& frameData) = 0;
		virtual uint32_t pushConstSize() = 0;
		virtual uint32_t uniformSize() = 0;

		VulkanDescriptorPool descriptorPool;
		vector<VulkanBuffer*> uniformBuffers;
		vector<VkDescriptorSet> descriptorSets;
		VkPipelineLayout pipelineLayout;
		ShaderProgram(const ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&);
	};
}

#endif //SHADERPROGRAM_HPP