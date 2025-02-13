
#include "physics-engine/PhysicsBody.h"
#include "core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

	PhysicsBody::PhysicsBody(){
        PhysicsEngine::get()->physicsBodies.push_back(this);
    }

    void PhysicsBody::physics_update(float pStep) {
        
        if(type == phys_type::STATIC) return;

        acceleration += PhysicsEngine::get()->gravity;
        velosity += acceleration*pStep;
        getTransform().Translate(velosity*pStep);
        acceleration = glm::vec3(0);
    }

    void PhysicsBody::addForce(glm::vec3 force, bool impulse){
        if(impulse)
            velosity += force;
        else   
            acceleration += force;
    }
}