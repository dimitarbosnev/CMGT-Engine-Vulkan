#ifndef TESTMATERIAL_HPP
#define TESTMATERIAL_HPP

#pragma once
#include "glm.hpp"
#include "Material.hpp"
#include "GraphicsPipeline.hpp"
using namespace glm;
using namespace std;

namespace cmgt {

	class TestMaterial : public Material
	{
	public:

		TestMaterial();
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	private:
		virtual void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) override;
		void bindPipeline(VkCommandBuffer commandBuffer) override;
		virtual GraphicsPipeline* getPipeline() override { return _pipeline; }
		inline static GraphicsPipeline* _pipeline = nullptr;
		static void _lazyInitializeShader();
	};
}
#endif // TESTMATERIAL_HPP
