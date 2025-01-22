#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#pragma once
#include "core/paths.h"
#include "core/config.h"
#include<string>
#include<vector>
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanSwapchain.h"
#include "render-engine/VulkanRenderer.h"
#include "render-engine/VulkanBuffer.h"
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