#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"

namespace cmgt
{
	enum class phys_type { STATIC, DYNAMIC };
	class PhysicsBody : public Component
	{
	public:
		PhysicsBody();
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void physics_update(float pStep) override;
		void setMass(float m){ mass = m; }
		float getInverseMass(){ 
			if(type == phys_type::DYNAMIC)
				return 1/mass;
			else
				return 0;
		 }
		void setPhysType(phys_type t){ type = t; }
		phys_type getPhysType() { return type; }
		void addForce(glm::vec3 force, bool impulse = false);
		glm::vec3 velosity = glm::vec3(0);
		glm::vec3 acceleration = glm::vec3(0);
	private:
		float mass = 1;
		phys_type type = phys_type::DYNAMIC;
		//disallow copy and assignment
		PhysicsBody(const PhysicsBody&);
		PhysicsBody& operator=(const PhysicsBody&);
	};
} 
#endif // PHYSICSBODY_H