
#include "utils/TestMaterial.h"
#include "core/BasicShaderProgram.h"
#include "core/paths.h"
#include<iostream>
namespace cmgt {
	TestMaterial::TestMaterial()
	{
		if (!_pipeline)
			_lazyInitializeShader();
	}
	void TestMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		BasicShaderProgram::BasicPushConstData data;
		data.mvpMatrix = frameData.projectionMatrix * glm::inverse(frameData.viewMatrix) * pModelMatrix;
		//data.modelMatrix = glm::transpose(glm::inverse(pModelMatrix));
		//data.mvpMatrix = pModelMatrix;
		data.normalMatrix = glm::transpose(glm::inverse(pModelMatrix));
		_pipeline->setPushConstants(frameData.commandBuffer, &data);
	}
	void TestMaterial::bindPipeline(VkCommandBuffer commandBuffer)
	{
		_pipeline->bind(commandBuffer);
	}
	void TestMaterial::_lazyInitializeShader()
	{
		_pipeline = new GraphicsPipeline(new BasicShaderProgram("vert.spv","frag.spv"));
	}
}
