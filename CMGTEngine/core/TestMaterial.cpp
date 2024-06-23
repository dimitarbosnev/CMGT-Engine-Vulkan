#pragma once
#include "TestMaterial.hpp"
#include "BasicShaderProgram.hpp"
#include "paths.hpp"
namespace cmgt {
	TestMaterial::TestMaterial()
	{
		if (!_pipeline)
			_lazyInitializeShader();
	}
	void TestMaterial::bindPushConstants(VkCommandBuffer commandBuffer, const mat4& pModelMatrix, const mat4& pViewMatrix, const mat4& pPerspectiveMatrix){

		BasicShaderProgram::BasicPushConstData data;
		data.mvpMatrix = pPerspectiveMatrix * glm::inverse(pViewMatrix) * pModelMatrix;
		data.time = (float)glfwGetTime();
		_pipeline->setPushConstants(commandBuffer, &data);
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
