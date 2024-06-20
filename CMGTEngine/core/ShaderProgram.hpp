#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
using namespace std;

namespace cmgt {
	class ShaderProgram {
	public:

		ShaderProgram(	const string& vertexFile, 
						const string& fragmentFile, 
						const string& tessellationControlFile = "", 
						const string& tessellationEvaluationFile = "", 
						const string& geometryFile = "");
		~ShaderProgram();
		void CreatePipelineShaderStages(VkGraphicsPipelineCreateInfo& pipelineInfo);
	private:
		static vector<char> readFile(const string& filepath);

		void CreateShader(const string& shaderFile, VkShaderModule* module);
		void CreateShaderModule(const vector<char>& shader, VkShaderModule* module);

		VkShaderModule vertexShaderModule;
		VkShaderModule tessellationControlShaderModule;
		VkShaderModule tessellationEvaluationShaderModule;
		VkShaderModule geometryShaderModule;
		VkShaderModule fragmentShaderModule;

		ShaderProgram(const ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&);
	};
}

#endif //SHADERPROGRAM_HPP