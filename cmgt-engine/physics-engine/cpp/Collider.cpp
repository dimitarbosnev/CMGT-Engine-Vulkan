
#include "physics-engine/Collider.h"
#include "core/GameObject.h"
#include "physics-engine/Shape.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    Collider::Collider() {
        PhysicsEngine::get()->addCollider(this);
    }


    void Collider::update(float pStep) {
    }

    std::pair<float, float> Collider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {
        // Initialize with extreme values
        float minProj = MAX;
        float maxProj = -MAX;

        for (const glm::vec3& vert : shape.colliderMesh) {
            //projection
            float proj = glm::dot(vert, axis);
            minProj = std::min(minProj, proj);
            maxProj = std::max(maxProj, proj);
        }

        return {minProj, maxProj};
    }

    glm::vec3 Collider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        glm::vec3 furthestVert;
        float value = -MAX;
        for (glm::vec3 vert : shape.colliderMesh)
        {
            float temp = glm::dot(vert, dir);
            if (temp > value)
            {
                furthestVert = vert;
                value = temp;
            }
        }

        //return the furthes vertex
        return  furthestVert;
    }
}