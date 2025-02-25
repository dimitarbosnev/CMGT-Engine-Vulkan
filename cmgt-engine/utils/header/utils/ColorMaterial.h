#ifndef COLORMATERIAL_H
#define COLORMATERIAL_H

#pragma once
#include "minimal/glm.h"
#include "core/Material.h"
#include "core/GraphicsPipeline.h"
#include "core/Globals.h"

namespace cmgt {

	class ColorMaterial : public Material
	{
	public:
		struct PushConstData
		{
			glm::mat4 normalMatrix;
			alignas(16) glm::vec3 color;
		};
		struct UniformData {

		};
		ColorMaterial();
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	public:
		glm::vec3 color = glm::vec3(0.7f);
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
#endif // COLORMATERIAL_H
