
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

        velocity += acceleration*pStep;
        float speed = glm::length(velocity);
        // F_drag = -0.5 * rho * Cd * A * speed^2 * (velocity / speed)
        //A = cross sectional area
        glm::vec3 quadraticAccel = (-0.5f * AIR_DENSITY * DRAG_COEF * 1.f * speed * speed * (velocity / speed)) / mass;
        velocity += quadraticAccel*pStep;
        getTransform().Translate(velocity*pStep);
        acceleration = glm::vec3(0);
    }

    void PhysicsBody::addForce(glm::vec3 force, bool impulse){
        if(impulse)
            velocity += force;
        else   
            acceleration += force;
    }

    void PhysicsBody::reflectVelosity(const glm::vec3& collNormal){
        velocity -= 2.f* glm::dot(velocity,collNormal) * collNormal;
    }
}