#ifndef SHADERPROGRAM_HPP
#define SHDAERPROGRAM_HPP

#pragma once
#include "paths.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
using namespace std;

namespace cmgt {
	struct ShaderProgramInfo
	{
		ShaderProgramInfo() = default;
		ShaderProgramInfo(const ShaderProgramInfo&) = delete;
		ShaderProgramInfo& operator=(const ShaderProgramInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	struct PushConstantData {
		vec2 offset;
		alignas(16) vec3 color;
	};
	class ShaderProgram {
	public:
		ShaderProgram(const string& vertexFile, const string& fragmentFile);
		~ShaderProgram();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultShaderProgramInfo(ShaderProgramInfo& configInfo);
	private:
		void createPipelineLayout();
		void createPipeline(ShaderProgramInfo& pipelineConfig);
		void recreateSwapchain();
		void createCommandBuffers();
		void freeCommandBuffers();
		void recordCommandBuffer(int imageIndex);

		static vector<char> readFile(const string& filepath);
		void CreateShaderProgram(const string& vertexFile, const string& fragmentFile, const ShaderProgramInfo& info);
		void CreateShaderModule(const vector<char>& shader, VkShaderModule* module);
		vector<VkCommandBuffer> commandBuffers;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
	};
}
#endif // SHADERPROGRAM_HPP