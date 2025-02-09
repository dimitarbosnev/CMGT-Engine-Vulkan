
#include "physics-engine/Shape.h"
#include "core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    Shape::Shape(Collider*pCollider) : collider(pCollider){

        worldTransform = collider->getTransform().getWorldTransform();
        for(const glm::vec3& vert : collider->colliderMesh){
            glm::vec3 point = vert;
            point = worldTransform * glm::vec4(point,1);
            colliderMesh.push_back(point);
        }
        //Centroid
        if(colliderMesh.size() > 0)
        centroid = getCentroid(colliderMesh);
        else centroid = worldTransform[3].xyz();
        
    }

    glm::vec3 Shape::getCentroid(const std::list<glm::vec3>& vertecies){
        glm::vec3 vecSum = glm::vec3(0);
        for(glm::vec3 vert : vertecies){
            vecSum += vert;
        }
        return vecSum/vertecies.size();
    }
}