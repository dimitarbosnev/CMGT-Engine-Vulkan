#ifndef BASICSHADERPROGRAM_H
#define BASICSHADERPROGRAM_H
#pragma once
#include "paths.h"
#include "config.h"
#include "render-engine/VulkanInstance.h"
#include "ShaderProgram.h"
#include "render-engine/VulkanRenderer.h"
#include "glm.h"
#include<string>
#include<vector>
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

#endif //BASICSHADERPROGRAM_H