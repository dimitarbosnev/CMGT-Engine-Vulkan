#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include <vector>
#include <list>
namespace cmgt
{
	class Collider;
	class PhysicsBody;
	struct Shape;
	class PhysicsEngine : public Singelton<PhysicsEngine>
	{
		friend class PhysicsBody;
	public:
		PhysicsEngine();
		~PhysicsEngine();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep); 
		const glm::vec3& getGravity() { return gravity; }
		void addCollider(Collider* collider){colliders.push_back(collider);}
	private:
		glm::vec3 gravity;
		static std::vector<glm::vec3> checkCollision(Shape& shape1, Shape& shape2);
		static glm::vec3 getSupportPoint(Shape& shape1, Shape& shape2, glm::vec3 dir);
		static glm::vec3 getFurthestPoint(Shape& shape1,glm::vec3 dir);
		static bool loopCheck(glm::vec3 simplex[4],Shape& shape1, Shape& shape2);

		//disallow copy and assignment
		PhysicsEngine(const PhysicsEngine&);
		PhysicsEngine& operator=(const PhysicsEngine&);
		std::vector<PhysicsBody*> physicsBodies = {};
		std::vector<Collider*> colliders = {};
	};
} 
#endif // PHYSICSENGINE_H