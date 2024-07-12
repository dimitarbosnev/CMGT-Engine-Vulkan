#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include "glm.hpp"
#include<string>
#include<vector>
#include<list>
#include "VulkanInstance.hpp"
#include "ShaderProgram.hpp"
#include "VulkanDescriptor.hpp"
using namespace std;

namespace cmgt {
	class Mesh;
	class VulkanBuffer;
	struct GraphicsPipelineInfo
	{
		GraphicsPipelineInfo() = default;
		GraphicsPipelineInfo(const GraphicsPipelineInfo&) = delete;
		GraphicsPipelineInfo& operator=(const GraphicsPipelineInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};
	struct UniformData {
		glm::mat4 cameraMatrix;
		glm::mat4 projMatrix;
		glm::vec4 ambientLight;
		glm::vec4 dirLight;
	};

	class GraphicsPipeline {
	public:
		GraphicsPipeline(const GraphicsPipelineInfo& info, uint8_t pPushConstSize, ShaderProgram* pShaderProgram);
		GraphicsPipeline(uint8_t pPushConstSize, ShaderProgram* pShaderProgram);
		~GraphicsPipeline();

		void bind(VkCommandBuffer commandBuffer);
		static void defaultGraphicsPipelineInfo(GraphicsPipelineInfo& configInfo);

		void setPushConstants(VkCommandBuffer commandBuffer, const void* pData);
		void createPipeline();
		void renderMeshes(int imageIndex, VkCommandBuffer commandBuffer, const glm::mat4& pViewMatrix, const glm::mat4& pPerspectiveMatrix);
		void AddMeshToRender(Mesh* mesh);
		void RemoveFromRenderer(Mesh* mesh);
	private:
		void creatPipelineLayout();
		void createPipeline(const GraphicsPipelineInfo& info);
		VulkanDescriptorPool descriptorPool;
		vector<VulkanBuffer*> uniformBuffers;
		vector<VkDescriptorSet> descriptorSets;
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
		ShaderProgram* shaderProgram;
		uint8_t pushConstSize;
		list<Mesh*> meshesToRender;
		GraphicsPipeline(const GraphicsPipeline&);
		GraphicsPipeline& operator=(const GraphicsPipeline&);
	};
}

#endif //GRAPHICSPIPELINE_HPP