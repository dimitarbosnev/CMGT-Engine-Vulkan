#ifndef TESTMATERIAL_HPP
#define TESTMATERIAL_HPP

#pragma once
#include "glm.hpp"
#include "Material.hpp"
#include "GraphicsPipeline.hpp"
using namespace glm;
using namespace std;

namespace cmgt {
	class GameObject;
	class Mesh;
	class World;

	class TestMaterial : public Material
	{
	public:
		TestMaterial();
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
		virtual void bindPushConstants(VkCommandBuffer commandBuffer, const mat4& pModelMatrix, const mat4& pViewMatrix, const mat4& pPerspectiveMatrix) override;
		void bindPipeline(VkCommandBuffer commandBuffer) override;
	private:
		inline static GraphicsPipeline* _pipeline = nullptr;
		static void _lazyInitializeShader();
	};
}
#endif // TESTMATERIAL_HPP
