
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
namespace cmgt{

    void PhysicsEngine::InitializePhysics() { assignInstance(new PhysicsEngine()); }

	PhysicsEngine::PhysicsEngine() {
    }

    PhysicsEngine::~PhysicsEngine() {

    }


    void PhysicsEngine::update(float pStep) {
        //for (PhysicsBody& body : physicsBodies)
            //body.physicsStep(pStep);

        //for(int i = 0; i < physicsBodies.size(); i++)
            //for (int j = i + 1; j < physicsBodies.size(); j++) {
                //checkCollision(*physicsBodies[i].getCollider(), *physicsBodies[j].getCollider());
           //}
    }

    void PhysicsEngine::checkCollision(SphereCollider& collider1, SphereCollider& collider2)
    {
    }

    void PhysicsEngine::checkCollision(SphereCollider& collider1, PlaneCollider& collider2)
    {
    }

    void PhysicsEngine::checkCollision(PlaneCollider& collider1, PlaneCollider& collider2)
    {
    }

}