#ifndef LIGHT_HPP
#define LIGHT_HPP

#pragma once
#include <string>
#include "../glm.hpp"
#include "Component.hpp"

using namespace glm;
using namespace std;
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
		Light(const string& aName = nullptr, const vec3& aPosition = vec3(2.0f, 10.0f, 5.0f), 
			LightType type = Ambient, GameObject* pOwner = nullptr);
		~Light() override;

		virtual void setOwner(GameObject* pOwner) override;
		virtual void update(float pStep) override;

		void setLightColor(vec3 color) {
			this->_color = vec4(color, _color.w);
		};
		void setLightColor(float r, float g, float b) {
			this->setLightColor(vec3(r, g, b));
		};
		void setIntencity(float intencity) {
			_color.w = intencity;
		};
		void setRange(float range) {
			_range = range;
		};
		void setDirection(vec3 direction) {
			this->_direction = direction;
		};
		void setDirection(float x, float y, float z) {
			setDirection(vec3(x, y, z));
		};

		void setDirection(mat3 transform) {
			setDirection(transform * vec3(1));
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
		vec4 _color = vec4(1);
		vec3 _direction = vec3(1);
		float _range;
		LightType _type;

	};
}
#endif // LIGHT_HPP