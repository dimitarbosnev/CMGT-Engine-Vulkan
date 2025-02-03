#ifndef TESTMATERIAL_H
#define TESTMATERIAL_H

#pragma once
#include "minimal/glm.h"
#include "core/Material.h"
#include "vulkan-api/GraphicsPipeline.h"
#include "vulkan-api/ShaderProgram.h"
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
	private:
		virtual void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) override;
		void bindPipeline(VkCommandBuffer commandBuffer) override;
		//virtual GraphicsPipeline* getPipeline() override { return &_pipeline; }
		//"vert.spv","frag.spv"
		static GraphicsPipeline pipeline;
	};
}
#endif // TESTMATERIAL_H
