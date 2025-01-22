#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once
#include "glm.h"

namespace cmgt
{
	class GameObject;

	class Component
	{
	public:

		Component();
		virtual ~Component();

		//for internal administration, do not use directly
		virtual void setOwner(GameObject* pGameObject);

		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep);

		const glm::mat4& getTransform();
	protected:

		GameObject* _owner;

	private:

		//disallow copy and assignment
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
	};
} 
#endif // COMPONENT_H