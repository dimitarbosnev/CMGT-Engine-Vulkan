
#include "physics-engine/PlaneCollider.h"
#include"core/GameObject.h"
namespace cmgt{

    PlaneCollider::PlaneCollider() : Collider() {
        colliderMesh.push_back(glm::vec3(1,1,0));
        colliderMesh.push_back(glm::vec3(1,-1,0));
        colliderMesh.push_back(glm::vec3(-1,-1,0));
        colliderMesh.push_back(glm::vec3(-1,1,0));
    }


    void PlaneCollider::update(float pStep) {
    }
}