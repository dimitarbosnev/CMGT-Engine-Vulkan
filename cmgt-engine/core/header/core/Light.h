#ifndef LIGHT_H
#define LIGHT_H

#pragma once
#include <string>
#include "minimal/glm.h"
#include "core/Component.h"

namespace cmgt {

	class GameObject;

	enum LightType {
		Ambient = 0,
		Directional = 1,
		Point = 2,
	};
	class Light : public Component
	{
	public:
		Light(LightType type = Ambient);
		~Light() override;

		virtual void update(float pStep) override;

		void setLightColor(glm::vec3 color) {
			this->_color = glm::vec4(color, _color.w);
		};
		void setLightColor(float r, float g, float b) {
			this->setLightColor(glm::vec3(r, g, b));
		};
		void setIntencity(float intencity) {
			_color.w = intencity;
		};
		void setRange(float range) {
			_range = range;
		};
		void setDirection(glm::vec3 direction) {
			this->_direction = direction;
		};
		void setDirection(float x, float y, float z) {
			setDirection(glm::vec3(x, y, z));
		};

		void setDirection(glm::mat3 transform) {
			setDirection(transform * glm::vec3(1));
		};

		//override set parent to register/deregister light...
		/*
		* ambient light = [color,intencity]
		*
		* directional light = [color, intencity]
		*					  [direction, empty]
		*
		* point light = [color, intencity]
		*				[position,  range]
		*/
	protected:
		virtual void OnSetOwner() override;
		glm::vec4 _color = glm::vec4(1);
		glm::vec3 _direction = glm::vec3(1);
		float _range;
		LightType _type;

	};
}
#endif // LIGHT_H