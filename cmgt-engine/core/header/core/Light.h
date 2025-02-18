#ifndef LIGHT_H
#define LIGHT_H

#pragma once
#include <string>
#include "minimal/glm.h"
#include "core/Component.h"
#include "minimal/types.h"
namespace cmgt {

	class GameObject;
	class Light : public Component
	{
	public:
		Light(LightType type = LightType::Ambient);
		~Light() override;

		virtual void update(float pStep) override;

		void setLightColor(glm::vec3 color) {
			this->_color = color;
		};
		void setLightColor(float r, float g, float b) {
			this->setLightColor(glm::vec3(r, g, b));
		};
		void setIntencity(float intencity) {
			_intencity = intencity;
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

	protected:
		virtual void OnSetOwner() override;
		LightType _type = LightType::Ambient;
		glm::vec3 _color = glm::vec3(0);
		glm::vec3 _direction = glm::vec3(0);
		glm::vec3 _position = glm::vec3(0);
		glm::vec3 _cut_off_angle = glm::vec3(0);
		float _intencity = 0;
		float _range = 0;

	};


	/*
	* ambient light = [color,intencity]
						[empty,empty]
	*
	* directional light = [color, intencity]
	*					  [direction, empty]
	*
	* point light = [color, intencity]
	*				[position,  range]
	*/
}
#endif // LIGHT_H