#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include "minimal/glm.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/GraphicsPipeline.h"
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanFrameData.h"

namespace cmgt {
	class GameObject;
	class Mesh;
	class World;


	class Material
	{
	public:
		Material() = default;
		virtual ~Material() = default;
		void setShineColor(glm::vec3 color) {
			this->_shininess = glm::vec4(color, _shininess.w);
		};
		void setShineColor(float r, float g, float b) {
			this->setShineColor(glm::vec3(r, g, b));
		};
		void setShinines(float shininess) {
			this->_shininess.w = shininess;
		};
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	protected:
		glm::vec4 _shininess = glm::vec4(1);
		virtual void bindPipeline(VkCommandBuffer commandBuffer) = 0;
		virtual void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) = 0;
		virtual GraphicsPipeline* getPipeline() = 0;
		friend class Mesh;
	};
}
#endif // MATERIAL_H
