
#include "physics-engine/PhysicsBody.h"
#include "core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

	PhysicsBody::PhysicsBody(){
        PhysicsEngine::get()->physicsBodies.push_back(this);
    }

    void PhysicsBody::physics_update(float pStep) {
        
        if(type == phys_type::STATIC) return;
        //gravity check here
        if(useGravity())
            acceleration += PhysicsEngine::get()->gravity;

        velocity += acceleration*pStep;
        float speed = glm::length(velocity);
        // F_drag = -0.5 * rho * Cd * A * speed^2 * (velocity / speed)
        //A = cross sectional area
        if(speed > 0 ){
        glm::vec3 quadraticAccel = (-0.5f * AIR_DENSITY * DRAG_COEF * 1.f * speed * speed * (velocity / speed)) / mass * pStep;
        velocity += quadraticAccel*pStep;
        getTransform().WorldTranslate(velocity*pStep);
        }
        acceleration = glm::vec3(0);

        //CHECK IF IT WORKS
        //angularVelosity += angularAcceleration * pStep;
        //float angleSpeed = glm::length(angularVelosity);
        //// F_drag = -0.5 * rho * Cd * A * speed^2 * (velocity / speed)
        ////A = cross sectional area
        //
        //if(angleSpeed > 1){
        //    glm::vec3 quadraticAngleAccel = (-0.5f * AIR_DENSITY * DRAG_COEF * 1.f * angleSpeed * angleSpeed * (angularVelosity / angleSpeed)) / mass * pStep;
        //    angularVelosity += quadraticAngleAccel * pStep;
        //    float angle = glm::length(angularVelosity);
        //    glm::vec3 axis = glm::normalize(angularVelosity);
        //    getTransform().Rotate(angle*pStep, axis);
        //}

    }

    void PhysicsBody::update(float pStep) {
        
        if(type == phys_type::STATIC) return;

    }

    void PhysicsBody::addForce(glm::vec3 force, bool impulse){
        if(impulse)
            velocity += force;
        else   
            acceleration += force;
    }

    glm::vec3 PhysicsBody::reflectVelosity(const glm::vec3& collNormal){
        //bounciness value can be added here
        float bounciness = 1.0f;
        return bounciness * (-2.f* glm::dot(velocity, collNormal) * collNormal + velocity);
    }
}