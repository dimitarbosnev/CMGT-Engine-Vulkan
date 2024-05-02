#pragma once
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
using namespace std;

namespace cmgt {
	struct ShaderProgramInfo
	{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};
	class ShaderProgram {
	public:
		ShaderProgram(VulkanInstance& instance, const string& vertexFile, const string& fragmentFile, const ShaderProgramInfo info);
		~ShaderProgram();

		static ShaderProgramInfo defaultShaderProgramInfo(uint32_t width, uint32_t height);
	private:
		static vector<char> readFile(const string& filepath);

		void CreateShaderProgram(const string& vertexFile, const string& fragmentFile, const ShaderProgramInfo& info);
		void CreateShaderModule(const vector<char>& shader, VkShaderModule* module);
		VulkanInstance& instance;
		VkPipeline graphicsPipeline;
		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
	};
}