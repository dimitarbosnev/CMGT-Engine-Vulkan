#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include "core/glm.h"
#include "core/config.h"
#include <vector>
using namespace glm;
namespace cmgt
{
	class PhysicsBody;
	class SphereCollider;
	class PlaneCollider;
	class PhysicsEngine : public Singleton<PhysicsEngine>
	{
	public:
		static void InitializePhysics();
		PhysicsEngine();
		~PhysicsEngine();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep); 
		const glm::vec3& getGravity() { return gravity; }
	private:
		glm::vec3 gravity;
		void checkCollision(SphereCollider& collider1, SphereCollider& collider2);
		void checkCollision(SphereCollider& collider1, PlaneCollider& collider2);
		void checkCollision(PlaneCollider& collider1, PlaneCollider& collider2);
		//disallow copy and assignment
		PhysicsEngine(const PhysicsEngine&);
		PhysicsEngine& operator=(const PhysicsEngine&);
		vector<PhysicsBody*> physicsBodies = {};
	};
} 
#endif // PHYSICSENGINE_H