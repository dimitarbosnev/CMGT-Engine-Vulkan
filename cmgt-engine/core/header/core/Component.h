#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once
#include "minimal/glm.h"
#include "core/Object.h"
#include "core/Transform.h"
namespace cmgt
{
	class GameObject;

	class Component : public Object
	{
		friend class GameObject;
	public:

		Component();

		virtual ~Component();
		//for internal administration, do not use directly
		
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep);
		
		Transform& getTransform();
		const GameObject* getOwner(){ return _owner;}
	protected:	
		GameObject* _owner;
		virtual void OnSetOwner();
	private:
		void setOwner(GameObject* pGameObject);
		//disallow copy and assignment
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
	};
} 
#endif // COMPONENT_H