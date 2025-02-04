
#include "utils/TestMaterial.h"
#include "vulkan-api/ShaderProgram.h"
#include "minimal/paths.h"
#include "core/Globals.h"
#include<iostream>
namespace cmgt {

	GraphicsPipeline TestMaterial::pipeline(GraphicsPipeline::defaultGraphicsPipelineInfo(),ShaderProgram("vert.spv","frag.spv",sizeof(TestPushConstData),sizeof(TestUniformData),*vulkanInstance),*vulkanSwapchain);
	
	TestMaterial::TestMaterial()
	{

	}
	void TestMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		TestPushConstData data;
		data.mvpMatrix = frameData.projectionMatrix * glm::inverse(frameData.viewMatrix) * pModelMatrix;
		//data.modelMatrix = glm::transpose(glm::inverse(pModelMatrix));
		//data.mvpMatrix = pModelMatrix;
		data.normalMatrix = glm::transpose(glm::inverse(pModelMatrix));
		pipeline.writePushConstants(frameData.commandBuffer, &data);
	}
	void TestMaterial::bindPipeline(VkCommandBuffer commandBuffer)
	{
		pipeline.bind(commandBuffer);
	}
}
