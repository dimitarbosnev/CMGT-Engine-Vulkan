
#include "core/GraphicsPipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <filesystem>
#include "vulkan-api/VulkanSwapchain.h"
#include "core/VulkanRenderer.h"
#include "core/Mesh.h"
#include "minimal/types.h"
namespace cmgt {

		std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		std::filesystem::path syspath = std::filesystem::canonical(std::filesystem::current_path());
		std::cout<<syspath<<filename<<std::endl;
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	void CreateShader(const std::string& shaderFile, VkShaderModule* module) {
		std::vector<char> shaderCode = readFile(CMGT_SHADER_PATH + shaderFile + ".spv");
		CreateShader(shaderCode, module);
	}

	void CreateShader(const std::vector<char>& shader, VkShaderModule* module) {

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = shader.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.data());

		if (vkCreateShaderModule(VulkanInstance::get()->device(), &createInfo, nullptr, module) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}

	GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineInfo& info, 
		std::function<VulkanDescriptorSetLayout(std::vector<size_t>&)> desriptorSetLayout, 
		std::function<VkPipelineShaderStageCreateInfo*(uint8_t&)> shadersStages,
		std::function<VkPushConstantRange*(uint8_t&)> pushConstants,
		std::function<void(const VulkanFrameData&)> uniformData,
		std::function<void()> deleteShaders) : 
		setDesriptorSetLayout(desriptorSetLayout), setPipelineShaderStages(shadersStages), setPushConstants(pushConstants), 
		setUniformData(uniformData), freeShaders(deleteShaders) {
		std::cout << " Creating Graphics Pipeline...\n";
		createPipelineLayout();

		createPipeline(info);
		std::cout << "Graphics Pipeline Initalized!\n";
		VulkanRenderer::get()->pipelines.push_back(this);
	}


	GraphicsPipeline::~GraphicsPipeline() {
		freeShaders();
		//clear meshes
		renderMeshs.clear();
		//clear buffers
		for (VulkanBuffer* buffer : descriptorBuffers)
			delete buffer;
		descriptorBuffers.clear();
		delete descriptorPool;
		vkDestroyPipelineLayout(VulkanInstance::get()->device(), _pipelineLayout, nullptr);
		vkDestroyPipeline(VulkanInstance::get()->device(), graphicsPipeline, nullptr);
		std::cout << "Pipeline destroyed" << std::endl;
	}
	void GraphicsPipeline::createPipelineLayout() {

		uint8_t i;
		VkPushConstantRange* ranges = setPushConstants(i);
		std::vector<size_t> sizes{};
		VulkanDescriptorSetLayout descriptorSetLayout = setDesriptorSetLayout(sizes);

		VulkanDescriptorPool::Builder poolBuilder(VulkanDescriptorPool::Builder().setMaxSets(MAX_FRAMES_IN_FLIGHT));

		for (int i = 0; i < sizes.size(); i++){
			poolBuilder.addPoolSize(descriptorSetLayout.getDescriptorSetLayoutBindingAt(i).descriptorType, MAX_FRAMES_IN_FLIGHT);
		}
		
		descriptorPool = new VulkanDescriptorPool(poolBuilder.build());

		VulkanInstance* VkInstance = VulkanInstance::get();
		descriptorBuffers.reserve(sizes.size());
		for (int i = 0; i < sizes.size(); i++) {
			VulkanBuffer* buffer = new VulkanBuffer(VkInstance->physicalDevice(), VkInstance->device(),sizes[i], MAX_FRAMES_IN_FLIGHT,
			descriptorSetLayout.getBufferUsageBasedOnBindingAt(i), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			descriptorBuffers.push_back(buffer);
			buffer->map();
		}

		descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {
			VulkanDescriptorWriter writer(descriptorSetLayout, *descriptorPool);
			
			for (int y = 0; y < sizes.size(); y++){
				VkDescriptorBufferInfo bufferInfo = descriptorBuffers[y]->descriptorInfo();
				writer.writeBuffer(y, &bufferInfo);		
			}

			if(!writer.build(descriptorSets[i])){
				throw std::runtime_error("failed to build descriptor set!");
			}
		}

		std::vector<VkDescriptorSetLayout> descriptorSetLayouts{ VulkanRenderer::get()->getDescriptorSetLayout(), descriptorSetLayout.getDescriptorSetLayout() };
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = i;
		pipelineLayoutInfo.pPushConstantRanges = ranges;
		if (vkCreatePipelineLayout(VulkanInstance::get()->device(), &pipelineLayoutInfo, nullptr, &_pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipelin layout");
		
		delete[] ranges;
	}
	

	void GraphicsPipeline::createPipeline(const GraphicsPipelineInfo& configInfo) {
		auto bindingDescriptions = Vertex::getBindingDescription();
		auto atttributeDescriptions = Vertex::getAttributeDescription();
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(atttributeDescriptions.size());
		vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
		vertexInputInfo.pVertexAttributeDescriptions = atttributeDescriptions.data();
		vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		//Change the number at some point
		uint8_t i;
		VkPipelineShaderStageCreateInfo* shaderStages = setPipelineShaderStages(i);
		
		pipelineInfo.stageCount = i;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
		pipelineInfo.pViewportState = &configInfo.viewportInfo;
		pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
		pipelineInfo.pMultisampleState = &configInfo.multisampleInfo;
		pipelineInfo.pColorBlendState = &configInfo.colorBlendInfo;
		pipelineInfo.pDepthStencilState = &configInfo.depthStencilInfo;
		pipelineInfo.pDynamicState = &configInfo.dynamicStateInfo;

		pipelineInfo.layout = _pipelineLayout;
		pipelineInfo.renderPass = VulkanSwapchain::get()->getRenderPass();
		pipelineInfo.subpass = configInfo.subpass;

		pipelineInfo.basePipelineIndex = -1;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(VulkanInstance::get()->device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline");
		delete[] shaderStages;
	}

	void GraphicsPipeline::scheduleToRender(Mesh* mesh){
		renderMeshs.push_back(mesh);
	}

	void GraphicsPipeline::writeUniformBuffers(const short& imageIndex, const VkCommandBuffer& commandBuffer, std::vector<const void*>& pData)
	{
		if(pData.size() != descriptorBuffers.size())
		throw std::runtime_error("Bad Data");

		for(int i = 0; i < descriptorBuffers.size(); i++){
			descriptorBuffers[i]->writeToIndex(pData[i], imageIndex);
			//descriptorBuffers[i]->flushIndex(imageIndex);
		}

		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 1, 1, &descriptorSets[imageIndex], 0, nullptr);
	}

	void GraphicsPipeline::recordFrameCommandBuffer(const VulkanFrameData& frameData){
		bind(frameData.commandBuffer);

		//Write UniformData
		setUniformData(frameData);

		//CallRenderOnAllMeshes
		for(Mesh* mesh : renderMeshs){
			mesh->render(frameData);
		}
		renderMeshs.clear();
	}

	void GraphicsPipeline::bind(VkCommandBuffer commandBuffer) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,graphicsPipeline);
	}

	void GraphicsPipeline::defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo) {

		configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		configInfo.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
		configInfo.inputAssemblyInfo.pNext = NULL;
		configInfo.inputAssemblyInfo.flags = 0;

		configInfo.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		configInfo.viewportInfo.viewportCount = 1;
		configInfo.viewportInfo.pViewports = nullptr;
		configInfo.viewportInfo.scissorCount = 1;
		configInfo.viewportInfo.pScissors = nullptr;
		configInfo.viewportInfo.flags = 0;

		configInfo.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		configInfo.rasterizationInfo.depthClampEnable = VK_FALSE;
		configInfo.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
		configInfo.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
		configInfo.rasterizationInfo.lineWidth = 1.0f;
		configInfo.rasterizationInfo.cullMode = VK_CULL_MODE_NONE;
		configInfo.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		configInfo.rasterizationInfo.depthBiasEnable = VK_FALSE;
		configInfo.rasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
		configInfo.rasterizationInfo.depthBiasClamp = 0.0f;           // Optional
		configInfo.rasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

		configInfo.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		configInfo.multisampleInfo.sampleShadingEnable = VK_FALSE;
		configInfo.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		configInfo.multisampleInfo.minSampleShading = 1.0f;           // Optional
		configInfo.multisampleInfo.pSampleMask = nullptr;             // Optional
		configInfo.multisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
		configInfo.multisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional
		configInfo.multisampleInfo.pNext = NULL;

		configInfo.colorBlendAttachment.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT;
		configInfo.colorBlendAttachment.blendEnable = VK_FALSE;
		configInfo.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
		configInfo.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
		configInfo.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
		configInfo.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
		configInfo.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
		configInfo.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

		configInfo.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		configInfo.colorBlendInfo.logicOpEnable = VK_FALSE;
		configInfo.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
		configInfo.colorBlendInfo.attachmentCount = 1;
		configInfo.colorBlendInfo.pAttachments = &configInfo.colorBlendAttachment;
		configInfo.colorBlendInfo.blendConstants[0] = 0.0f;  // Optional
		configInfo.colorBlendInfo.blendConstants[1] = 0.0f;  // Optional
		configInfo.colorBlendInfo.blendConstants[2] = 0.0f;  // Optional
		configInfo.colorBlendInfo.blendConstants[3] = 0.0f;  // Optional

		configInfo.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		configInfo.depthStencilInfo.depthTestEnable = VK_TRUE;
		configInfo.depthStencilInfo.depthWriteEnable = VK_TRUE;
		configInfo.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		configInfo.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		configInfo.depthStencilInfo.minDepthBounds = 0.0f;  // Optional
		configInfo.depthStencilInfo.maxDepthBounds = 1.0f;  // Optional
		configInfo.depthStencilInfo.stencilTestEnable = VK_FALSE;
		configInfo.depthStencilInfo.front = {};  // Optional
		configInfo.depthStencilInfo.back = {};   // Optional

		configInfo.dynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		configInfo.dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		configInfo.dynamicStateInfo.pDynamicStates = configInfo.dynamicStateEnables.data();
		configInfo.dynamicStateInfo.dynamicStateCount =
			static_cast<uint32_t>(configInfo.dynamicStateEnables.size());
		configInfo.dynamicStateInfo.flags = 0;
		configInfo.dynamicStateInfo.pNext = NULL;
	}

	GraphicsPipelineInfo GraphicsPipeline::defaultGraphicsPipelineInfo(){
		GraphicsPipelineInfo info;
		defaultGraphicsPipelineInfo(info);
		return info;
	}
}
