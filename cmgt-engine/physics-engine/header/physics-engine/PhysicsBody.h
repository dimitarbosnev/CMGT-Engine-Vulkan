#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"

namespace cmgt
{
	class PhysicsBody : public Component
	{
	public:
		PhysicsBody();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
	private:
		//disallow copy and assignment
		PhysicsBody(const PhysicsBody&);
		PhysicsBody& operator=(const PhysicsBody&);
	};
} 
#endif // PHYSICSBODY_H