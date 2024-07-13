#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#pragma once
#include "glm.hpp"
#include "VulkanInstance.hpp"
#include "GraphicsPipeline.hpp"
#include "VulkanRenderer.hpp"
using namespace glm;
using namespace std;

namespace cmgt {
	class GameObject;
	class Mesh;
	class World;


	class Material
	{
	public:
		Material() = default;
		virtual ~Material() = default;
		void setShineColor(vec3 color) {
			this->_shininess = vec4(color, _shininess.w);
		};
		void setShineColor(float r, float g, float b) {
			this->setShineColor(vec3(r, g, b));
		};
		void setShinines(float shininess) {
			this->_shininess.w = shininess;
		};
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	protected:
		vec4 _shininess = vec4(1);
		virtual void bindPipeline(VkCommandBuffer commandBuffer) = 0;
		virtual void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) = 0;
		virtual GraphicsPipeline* getPipeline() = 0;
		friend class Mesh;
	};
}
#endif // MATERIAL_HPP
