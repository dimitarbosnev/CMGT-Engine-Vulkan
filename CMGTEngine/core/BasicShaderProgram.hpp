#ifndef BASICSHADERPROGRAM_HPP
#define BASICSHADERPROGRAM_HPP
#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
#include "ShaderProgram.hpp"
#include "glm.hpp"
using namespace std;

namespace cmgt {
	class BasicShaderProgram : public ShaderProgram{
	public:
		BasicShaderProgram(const string& vertexFile, const string& fragmentFile);
		virtual ~BasicShaderProgram() override;
		void BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages) override;
		int stageSize() override;
	private:

		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;
	};
}

#endif //BASICSHADERPROGRAM_HPP