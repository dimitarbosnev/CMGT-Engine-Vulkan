
#include "physics-engine/SphereCollider.h"
#include"physics-engine/Shape.h"
#include"core/GameObject.h"
namespace cmgt{

    SphereCollider::SphereCollider() : Collider(){
    }


    void SphereCollider::update(float pStep) {
    }

    std::pair<float, float> SphereCollider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {
        // Initialize with extreme values
        float dot = glm::dot(shape.worldTransform[3].xyz(), axis);
        float minProj = dot - radius;
        float maxProj = dot + radius;

        return {minProj, maxProj};
    }

    glm::vec3 SphereCollider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        //return the furthes vertex
        return  shape.worldTransform[3].xyz() + (dir * radius);
    }
}