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
		~ShaderProgram() = default;
		virtual void BindPipelineShaderStages(VkGraphicsPipelineCreateInfo& pipelineInfo) = 0;
		VkPipelineLayout pipelineLayout;
	protected:
		static vector<char> readFile(const string& filepath);

		void CreateShader(const string& shaderFile, VkShaderModule* module);
		void CreateShader(const vector<char>& shader, VkShaderModule* module);
		virtual void creatPipelineLayout() = 0;
		ShaderProgram(const ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&);
	};
}

#endif //SHADERPROGRAM_HPP