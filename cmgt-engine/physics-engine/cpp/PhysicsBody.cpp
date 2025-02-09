
#include "physics-engine/PhysicsBody.h"
#include "core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

	PhysicsBody::PhysicsBody(){
        PhysicsEngine::get()->physicsBodies.push_back(this);
    }

    void PhysicsBody::update(float pStep) {
    }
}