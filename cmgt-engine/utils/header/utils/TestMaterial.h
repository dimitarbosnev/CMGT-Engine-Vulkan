#ifndef TESTMATERIAL_H
#define TESTMATERIAL_H

#pragma once
#include "minimal/glm.h"
#include "core/Material.h"
#include "core/GraphicsPipeline.h"
#include "core/Globals.h"

namespace cmgt {

	class TestMaterial : public Material
	{
	public:
		struct TestPushConstData
		{
			glm::mat4 mvpMatrix;
			glm::mat4 normalMatrix;
		};
		struct TestUniformData {
			glm::mat4 cameraMatrix;
			glm::mat4 projMatrix;
			glm::vec4 ambientLight;
			glm::vec4 dirLight;
		};
		TestMaterial();
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	public:
		GraphicsPipeline* getPipeline() override {return pipeline;}
	private:
		void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) override;
		//Uniform Buffers Are meant to be one for all instances of the material
		static void bindUniformBuffers(const VulkanFrameData&);
		static void initPipeline();
		static void freePipeline();
		static VkPipelineShaderStageCreateInfo* bindPipelineShaderStages(uint8_t& num);
		static VulkanDescriptorSetLayout createDescriptorSetLayout(uint32_t& uniformSize);
		static VkPushConstantRange setupPushConsts();

		inline static VkShaderModule vertexShaderModule = nullptr;
		inline static VkShaderModule fragmentShaderModule = nullptr;
		inline static GraphicsPipeline* pipeline = nullptr;
		//virtual GraphicsPipeline* getPipeline() override { return &_pipeline; }
		//"vert.spv","frag.spv"
	};
}
#endif // TESTMATERIAL_H
