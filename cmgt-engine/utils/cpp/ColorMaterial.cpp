
#include "utils/ColorMaterial.h"
#include "minimal/paths.h"
#include "core/Globals.h"
#include "minimal/log.h"
#include<iostream>
namespace cmgt {	
	ColorMaterial::ColorMaterial()
	{
		_name = "ColorMaterial";
		//For Everymaterial the pipeline should be initalized
		if(pipeline == nullptr){
			initPipeline();
		}
	}
	void ColorMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		PushConstData data;
		data.normalMatrix = pModelMatrix;
		data.color = color;

		vkCmdPushConstants(frameData.commandBuffer, pipeline->pipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstData), &data);	
	}
	void ColorMaterial::bindUniformBuffers(const VulkanFrameData& frameData){

		//UniformData uniformData;
		//uniformData.cameraMatrix = frameData.viewMatrix;
		//uniformData.projMatrix = frameData.projectionMatrix;
		//uniformData.lightCount = frameData.lights.size();
		//uniformData.vector_lights = frameData.lights.data();
		//pipeline->writeUniformBuffers(frameData.imageIndex, frameData.commandBuffer,&uniformData);
	}
	void ColorMaterial::initPipeline(){

		Log::msg("Initalizing Shaders...");

		CreateShader("ColorShader.vert", &vertexShaderModule);
		Log::msg("\t Vertex Shader Initalized!");

		CreateShader("ColorShader.frag", &fragmentShaderModule);
		Log::msg("\t Fragment Shader Initalized!");

		Log::msg("Initalizing ColorMaterial Pipeline...");
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages = bindPipelineShaderStages();
		VulkanUniformObject::Builder builder = createDescriptorSetLayout();
		std::vector<VkPushConstantRange> pushConstants = setupPushConsts();
		pipeline = new GraphicsPipeline(GraphicsPipeline::defaultGraphicsPipelineInfo(), builder, shaderStages, pushConstants, bindUniformBuffers,freePipeline);
		Log::msg("Initalizing ColorMaterial Complete!");

		Log::flush_buffer();
	}

	//has to be called somewhere
	void ColorMaterial::freePipeline(){
		vkDestroyShaderModule(VulkanInstance::get()->device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(VulkanInstance::get()->device(), fragmentShaderModule, nullptr);
	}
	std::vector<VkPipelineShaderStageCreateInfo> ColorMaterial::bindPipelineShaderStages()
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

	VulkanUniformObject::Builder ColorMaterial::createDescriptorSetLayout(){
		return VulkanUniformObject::Builder();
		//return VulkanDescriptorSetLayout::Builder().build();
	}
	std::vector<VkPushConstantRange> ColorMaterial::setupPushConsts()
	{
		std::vector<VkPushConstantRange> range(1);
		range[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range[0].offset = 0;
		range[0].size = sizeof(PushConstData);
		return range;
	}
}
