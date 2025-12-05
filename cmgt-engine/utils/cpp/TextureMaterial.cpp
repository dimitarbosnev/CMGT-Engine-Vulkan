
#include "utils/TextureMaterial.h"
#include "minimal/paths.h"
#include "core/Globals.h"
#include "minimal/log.h"
#include<iostream>
namespace cmgt {	
	TextureMaterial::TextureMaterial()
	{
		_name = "TextureMaterial";
		//For Everymaterial the pipeline should be initalized
		if(pipeline == nullptr){
			initPipeline();
		}
	}
	void TextureMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		PushConstData data;
		data.modelMatrix = pModelMatrix;

		vkCmdPushConstants(frameData.commandBuffer, pipeline->pipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstData), &data);	
	}
	void TextureMaterial::bindUniformBuffers(const VulkanFrameData& frameData){

	}
	void TextureMaterial::initPipeline(){

		Log::msg("Initalizing Shaders...");

		CreateShader("ColorShader.vert", &vertexShaderModule);
		Log::msg("\t Vertex Shader Initalized!");

		CreateShader("ColorShader.frag", &fragmentShaderModule);
		Log::msg("\t Fragment Shader Initalized!");

		Log::msg("Initalizing TextureMaterial Pipeline...");
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages = bindPipelineShaderStages();
		VulkanUniformObject::Builder builder = createDescriptorSetLayout();
		std::vector<VkPushConstantRange> pushConstants = setupPushConsts();
		
		pipeline = new GraphicsPipeline(GraphicsPipeline::defaultGraphicsPipelineInfo(), builder, nullptr, shaderStages, pushConstants, bindUniformBuffers,freePipeline);
		Log::msg("Initalizing TextureMaterial Complete!");

		Log::flush_buffer();
	}

	//has to be called somewhere
	void TextureMaterial::freePipeline(){
		vkDestroyShaderModule(VulkanInstance::get()->device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(VulkanInstance::get()->device(), fragmentShaderModule, nullptr);
	}
	std::vector<VkPipelineShaderStageCreateInfo> TextureMaterial::bindPipelineShaderStages()
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

	VulkanUniformObject::Builder TextureMaterial::createDescriptorSetLayout(){
		return VulkanUniformObject::Builder();
		//return VulkanDescriptorSetLayout::Builder().build();
	}
	std::vector<VkPushConstantRange> TextureMaterial::setupPushConsts()
	{
		std::vector<VkPushConstantRange> range(1);
		range[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range[0].offset = 0;
		range[0].size = sizeof(PushConstData);
		return range;
	}
}
