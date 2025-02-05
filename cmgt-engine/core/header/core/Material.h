#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include "minimal/glm.h"
#include "vulkan-api/VulkanInstance.h"
#include "core/GraphicsPipeline.h"
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanFrameData.h"
#include "core/Object.h"
namespace cmgt {
	class Mesh;
	class Material : public Object
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

		virtual GraphicsPipeline* getPipeline() = 0;
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
	protected:
		glm::vec4 _shininess = glm::vec4(1);
		//Push Constants are meant to vary between Meshes
		virtual void bindPushConstants(const VulkanFrameData& frameData, const glm::mat4 pModelMatrix) = 0;
		//Bind Pipeline can also be called once per frame for all materials as long as you don't bind smth else in between
		friend class Mesh;
	};
}
#endif // MATERIAL_H
