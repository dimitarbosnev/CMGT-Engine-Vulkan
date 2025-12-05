
#include "utils/TestMaterial.h"
#include "minimal/paths.h"
#include "core/Globals.h"
#include "minimal/log.h"
#include<iostream>
namespace cmgt {	
	TestMaterial::TestMaterial()
	{
		_name = "TestMaterial";
		//For Everymaterial the pipeline should be initalized
		if(pipeline == nullptr){
			initPipeline();
		}
	}
	void TestMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		PushConstData data;
		data.mvpMatrix = frameData.projectionMatrix * frameData.viewMatrix * pModelMatrix;
		data.normalMatrix = glm::transpose(glm::inverse(pModelMatrix));

		vkCmdPushConstants(frameData.commandBuffer, pipeline->pipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstData), &data);
	}
	void TestMaterial::bindUniformBuffers(const VulkanFrameData& frameData){

		UniformData uniformData;
		uniformData.dirLight = glm::vec4(glm::normalize(glm::vec3(1, -1, 1)), 1);
		uniformData.ambientLight = glm::vec4(1, 1, 1, .2f);
		std::vector<const void*> data {&uniformData};
		pipeline->writeUniformBuffers(frameData.imageIndex, frameData.commandBuffer,data);
	}
	void TestMaterial::initPipeline(){

		Log::msg("Initalizing Shaders...");

		CreateShader("BasicVertexShader.vert", &vertexShaderModule);
		Log::msg("\t Vertex Shader Initalized!");

		CreateShader("BasicFragmentShader.frag", &fragmentShaderModule);
		Log::msg("\t Fragment Shader Initalized!");

		Log::msg("Initalizing TestMaterial Pipeline...");
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages = bindPipelineShaderStages();
		VulkanUniformObject::Builder builder = createDescriptorSetLayout();
		std::vector<VkPushConstantRange> pushConstants = setupPushConsts();
		pipeline = new GraphicsPipeline(GraphicsPipeline::defaultGraphicsPipelineInfo(), builder, nullptr, shaderStages, pushConstants, bindUniformBuffers,freePipeline);
		
		Log::msg("Initalizing TestMaterial Complete!");

		Log::flush_buffer();
	}

	//has to be called somewhere
	void TestMaterial::freePipeline(){
		vkDestroyShaderModule(VulkanInstance::get()->device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(VulkanInstance::get()->device(), fragmentShaderModule, nullptr);
	}
	std::vector<VkPipelineShaderStageCreateInfo> TestMaterial::bindPipelineShaderStages()
	{
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages(2);

		shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStages[0].module = vertexShaderModule;
		shaderStages[0].pName = "main";
		shaderStages[0].flags = 0;
		shaderStages[0].pNext = nullptr;
		shaderStages[0].pSpecializationInfo = nullptr;

		shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStages[1].module = fragmentShaderModule;
		shaderStages[1].pName = "main";
		shaderStages[1].flags = 0;
		shaderStages[1].pNext = nullptr;
		shaderStages[1].pSpecializationInfo = nullptr;

		return shaderStages;
	}

	VulkanUniformObject::Builder TestMaterial::createDescriptorSetLayout(){
		return VulkanUniformObject::Builder().addBufferBinding(0,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(UniformData));
		//return VulkanDescriptorSetLayout::Builder().build();
	}

	std::vector<VkPushConstantRange> TestMaterial::setupPushConsts()
	{
		std::vector<VkPushConstantRange> range(1);
		range[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range[0].offset = 0;
		range[0].size = sizeof(PushConstData);
		return range;
	}
}
