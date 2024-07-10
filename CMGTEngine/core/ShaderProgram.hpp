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
		ShaderProgram() = default;
		virtual ~ShaderProgram();
		virtual void BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages) = 0;
		virtual int stageSize() = 0;
	protected:
		
		static vector<char> readFile(const string& filepath);
		void CreateShader(const string& shaderFile, VkShaderModule* module);
		void CreateShader(const vector<char>& shader, VkShaderModule* module);

		ShaderProgram(const ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&);
	};
}

#endif //SHADERPROGRAM_HPP