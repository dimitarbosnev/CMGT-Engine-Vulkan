#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H

#pragma once
#include "minimal/paths.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include "minimal/events.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanDescriptor.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include<vector>
#include<list>

namespace cmgt {
	class Mesh;

	std::vector<char> readFile(const std::string& filepath);
	void CreateShader(const std::string& shaderFile, VkShaderModule* module);
	void CreateShader(const std::vector<char>& shader, VkShaderModule* module);

	struct GraphicsPipelineInfo
	{
		GraphicsPipelineInfo() = default;

		VkPipelineViewportStateCreateInfo viewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo multisampleInfo{};
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
		std::vector<VkDynamicState> dynamicStateEnables{};
		VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
		uint32_t subpass = 0;
	};


	class GraphicsPipeline {
	public:
		GraphicsPipeline(const GraphicsPipelineInfo& info, 
		std::function<VulkanDescriptorSetLayout(std::vector<size_t>&)> desriptorSetLayout, 
		std::function<VkPipelineShaderStageCreateInfo*(uint8_t&)> shadersStages,
		std::function<VkPushConstantRange*(uint8_t&)> pushConstants,
		std::function<void(const VulkanFrameData&)> uniformData,
		std::function<void()> deleteShaders);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);
		static GraphicsPipelineInfo defaultGraphicsPipelineInfo();
		VkPipelineLayout pipelineLayout() {return _pipelineLayout;}
		void writeUniformBuffers(const short& imageIndex, const VkCommandBuffer& commandBuffer, const void* pData);
		void recordFrameCommandBuffer(const VulkanFrameData& frameData);
		void createPipelineLayout();
		void createPipeline();
		void scheduleToRender(Mesh* mesh);
		
	private:
		
		std::function<void(const VulkanFrameData&)> setUniformData;
		std::function<void()> freeShaders;
		std::function<VulkanDescriptorSetLayout(std::vector<size_t>&)> setDesriptorSetLayout;//have to be set
		std::function<VkPipelineShaderStageCreateInfo*(uint8_t&)> setPipelineShaderStages;//have to be set
		std::function<VkPushConstantRange*(uint8_t&)> setPushConstants;//have to be set
		std::list<Mesh*> renderMeshs;
		void createPipeline(const GraphicsPipelineInfo& info);
		VkPipelineLayout _pipelineLayout;
		VkPipeline graphicsPipeline;
		VulkanDescriptorPool descriptorPool;
		std::vector<VulkanBuffer*> uniformBuffers;
		std::vector<VkDescriptorSet> descriptorSets;
		
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_H