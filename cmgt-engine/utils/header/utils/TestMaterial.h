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
		struct PushConstData
		{
			glm::mat4 mvpMatrix;
			glm::mat4 normalMatrix;
		};
		struct UniformData {
			glm::vec4 dirLight;
			glm::vec4 ambientLight;
		};
		TestMaterial();
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	public:
		GraphicsPipeline* getPipeline() override {return pipeline;}
	private:
		void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) override;
		static void bindUniformBuffers(const VulkanFrameData&);
		static void initPipeline();
		static void freePipeline();
		static std::vector<VkPipelineShaderStageCreateInfo> bindPipelineShaderStages();
		static VulkanUniformObject::Builder createDescriptorSetLayout();
		static std::vector<VkPushConstantRange> setupPushConsts();

		inline static VkShaderModule vertexShaderModule = nullptr;
		inline static VkShaderModule fragmentShaderModule = nullptr;
		inline static GraphicsPipeline* pipeline = nullptr;
	};
}
#endif // TESTMATERIAL_H
