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
		struct BasicPushConstData
		{
			glm::mat4 mvpMatrix;
			float time;
		};
		BasicShaderProgram(const string& vertexFile, const string& fragmentFile);
		~BasicShaderProgram();
		void BindPipelineShaderStages(VkGraphicsPipelineCreateInfo& pipelineInfo) override;
		uint32_t pushConstSize() override;
	private:

		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;
	};
}

#endif //BASICSHADERPROGRAM_HPP