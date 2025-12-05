#ifndef GRAPHICSPIPELINE_H
#define GRAPHICSPIPELINE_H

#pragma once
#include "minimal/paths.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include "minimal/events.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanUniformObject.h"
#include "vulkan-api/VulkanFrameData.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanBuffer.h"
#include<vector>
#include<list>

namespace cmgt {
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
		VulkanUniformObject::Builder& pipelineUniformBuilder,
		VkDescriptorSetLayout instanceLayout,
		std::vector<VkPipelineShaderStageCreateInfo>& shadersStages,
		std::vector<VkPushConstantRange>& pushConstantRanges,
		std::function<void(const VulkanFrameData&)> uniformData,
		std::function<void()> deleteShaders);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);
		static GraphicsPipelineInfo defaultGraphicsPipelineInfo();
		VkPipelineLayout& pipelineLayout() {return _pipelineLayout;}
		void writeUniformBuffers(const short& imageIndex, const VkCommandBuffer& commandBuffer, std::vector<const void*>& pData);
		void recordFrameCommandBuffer(const VulkanFrameData& frameData);
		
		private:
		
		std::function<void(const VulkanFrameData&)> setUniformData;
		std::function<void()> freeShaders;
		void createPipelineLayout(std::vector<VkPushConstantRange>& ranges, VkDescriptorSetLayout instanceLayout);
		void createPipeline(const GraphicsPipelineInfo& info, std::vector<VkPipelineShaderStageCreateInfo>& shadersStages);
		VkPipelineLayout _pipelineLayout;
		VkPipeline graphicsPipeline;
		VulkanUniformObject uniformSets;
		std::vector<VkShaderModule> shaderModules;
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_H