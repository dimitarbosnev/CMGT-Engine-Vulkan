
#include "LoveMaterial.h"
#include<iostream>
namespace cmgt {	
	LoveMaterial::LoveMaterial()
	{
		_name = "LoveMaterial";
		//For Everymaterial the pipeline should be initalized
		if(pipeline == nullptr){
			initPipeline();
		}
	}
	void LoveMaterial::bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix){

		PushConstData data;
		data.mvpMatrix = frameData.projectionMatrix * glm::inverse(frameData.viewMatrix) * pModelMatrix;
		data.normalMatrix = glm::transpose(glm::inverse(pModelMatrix));

		vkCmdPushConstants(frameData.commandBuffer, pipeline->pipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstData), &data);
	}
	void LoveMaterial::bindUniformBuffers(const VulkanFrameData& frameData){

		VkExtent2D extend = Window::get()->getWindowExtend();

		UniformData uniformData;
		uniformData.cameraMatrix = frameData.viewMatrix;
		uniformData.projMatrix = frameData.projectionMatrix;
		uniformData.dirLight = glm::vec4(glm::normalize(glm::vec3(1, -1, 1)), 1.f);
		uniformData.ambientLight = glm::vec4(1, 1, 1, .2f);
		uniformData.windowSize = glm::vec2(extend.width,extend.height);

		pipeline->writeUniformBuffers(frameData.imageIndex, frameData.commandBuffer,&uniformData);
	}
	void LoveMaterial::initPipeline(){

		std::cout << "Initalizing Shaders...\n";
		CreateShader("LoveVertexShader.vert", &vertexShaderModule);
		std::cout << "\t Vertex Shader Initalized!\n";
		CreateShader("LoveFragmentShader.frag", &fragmentShaderModule);
		std::cout << "\t Fragment Shader Initalized!\n";

		pipeline = new GraphicsPipeline(GraphicsPipeline::defaultGraphicsPipelineInfo(), createDescriptorSetLayout, bindPipelineShaderStages, setupPushConsts, bindUniformBuffers,freePipeline);
		
	}

	//has to be called somewhere
	void LoveMaterial::freePipeline(){
		vkDestroyShaderModule(VulkanInstance::get()->device(), vertexShaderModule, nullptr);
		vkDestroyShaderModule(VulkanInstance::get()->device(), fragmentShaderModule, nullptr);
	}
	VkPipelineShaderStageCreateInfo* LoveMaterial::bindPipelineShaderStages(uint8_t& num)
	{
		num = 2;
		VkPipelineShaderStageCreateInfo* shaderStages = new VkPipelineShaderStageCreateInfo[num];
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

	VulkanDescriptorSetLayout LoveMaterial::createDescriptorSetLayout(uint32_t& uniformSize){
		uniformSize = sizeof(UniformData);
		return VulkanDescriptorSetLayout::Builder().addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT).build();
	}

	VkPushConstantRange LoveMaterial::setupPushConsts()
	{
		VkPushConstantRange range;
		range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		range.offset = 0;
		range.size = sizeof(PushConstData);
		return range;
	}
}
