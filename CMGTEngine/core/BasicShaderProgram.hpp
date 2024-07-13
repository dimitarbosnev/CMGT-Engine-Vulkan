#ifndef BASICSHADERPROGRAM_HPP
#define BASICSHADERPROGRAM_HPP
#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
#include "ShaderProgram.hpp"
#include "VulkanRenderer.hpp"
#include "glm.hpp"
using namespace std;

namespace cmgt {
	class BasicShaderProgram : public ShaderProgram{
	public:
		struct BasicPushConstData
		{
			glm::mat4 mvpMatrix;
			glm::mat4 normalMatrix;
		};
		struct UniformData {
			glm::mat4 cameraMatrix;
			glm::mat4 projMatrix;
			glm::vec4 ambientLight;
			glm::vec4 dirLight;
		};
		BasicShaderProgram(const string& vertexFile, const string& fragmentFile);
		virtual ~BasicShaderProgram() override;
		void BindPipelineShaderStages(VkPipelineShaderStageCreateInfo* shaderStages) override;
		int stageSize() override;
	private:
		void bindUniformBuffers(const VulkanFrameData& frameData) override;
		void createPipelineLayout() override;
		uint32_t pushConstSize() override;
		uint32_t uniformSize() override;
		VkShaderModule vertexShaderModule;
		VkShaderModule fragmentShaderModule;
	};
}

#endif //BASICSHADERPROGRAM_HPP