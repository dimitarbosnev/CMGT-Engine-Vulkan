
#include "physics-engine/BoxCollider.h"
#include"core/GameObject.h"
namespace cmgt{

    BoxCollider::BoxCollider() : Collider() {
        //upper plane
        colliderMesh.push_back(glm::vec3(1,1,1));
        colliderMesh.push_back(glm::vec3(1,-1,1));
        colliderMesh.push_back(glm::vec3(-1,-1,1));
        colliderMesh.push_back(glm::vec3(-1,1,1));

        //lower plane
        colliderMesh.push_back(glm::vec3(-1,1,-1));
        colliderMesh.push_back(glm::vec3(-1,-1,-1));
        colliderMesh.push_back(glm::vec3(1,-1,-1));
        colliderMesh.push_back(glm::vec3(1,1,-1));
    }


    void BoxCollider::update(float pStep) {
    }
}