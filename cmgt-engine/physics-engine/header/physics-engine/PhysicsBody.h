#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"

namespace cmgt
{
	class GameObject;
	class Collider;
	class PhysicsBody : public Component
	{
	public:
		PhysicsBody();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
		void physicsStep(float pStep);
		Collider* getCollider() { return _collider; }
	private:
		Collider* _collider;
		//disallow copy and assignment
		PhysicsBody(const PhysicsBody&);
		PhysicsBody& operator=(const PhysicsBody&);
	};
} 
#endif // PHYSICSBODY_H