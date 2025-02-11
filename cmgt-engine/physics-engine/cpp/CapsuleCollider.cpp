
#include "physics-engine/CapsuleCollider.h"
#include "physics-engine/Shape.h"
#include "core/GameObject.h"
namespace cmgt{

    CapsuleCollider::CapsuleCollider() : Collider(){
    }


    void CapsuleCollider::update(float pStep) {
    }

    std::pair<float, float> CapsuleCollider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {

        glm::mat3 rotationMatrix(
            glm::vec3(shape.worldTransform[0]) / glm::length(shape.worldTransform[0]),
            glm::vec3(shape.worldTransform[1]) / glm::length(shape.worldTransform[1]),
            glm::vec3(shape.worldTransform[2]) / glm::length(shape.worldTransform[2])
        );

        glm::vec3 worldOrientation = (rotationMatrix * orientation) * (height/2.f);

        glm::vec3 endpoint1 = shape.centroid + worldOrientation;
        glm::vec3 endpoint2 = shape.centroid - worldOrientation;

        float proj1 = glm::dot(endpoint1, axis);
        float proj2 = glm::dot(endpoint2, axis);

        float minProj = std::min(proj1, proj2) - radius;
        float maxProj = std::max(proj1, proj2) + radius;

        return {minProj, maxProj};
    }

    glm::vec3 CapsuleCollider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        //return the furthes vertex
        return  shape.worldTransform[3].xyz() + (dir * radius);
    }
}