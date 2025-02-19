
#include "physics-engine/PlaneCollider.h"
#include"core/GameObject.h"
namespace cmgt{

    PlaneCollider::PlaneCollider() : Collider() {
        glm::vec3 v1(1,0,1);
        glm::vec3 v2(1,0,-1);
        glm::vec3 v3(-1,0,1);
        glm::vec3 v4(-1,0,-1);
        glm::vec3 v11(1,-0.01f,1);
        glm::vec3 v12(1,-0.01f,-1);
        glm::vec3 v13(-1,-0.01f,1);
        glm::vec3 v14(-1,-0.01f,-1);

        colliderMesh.reserve(8);
        colliderMesh.push_back(v1);
        colliderMesh.push_back(v2);
        colliderMesh.push_back(v3);
        colliderMesh.push_back(v4);
        colliderMesh.push_back(v11);
        colliderMesh.push_back(v12);
        colliderMesh.push_back(v13);
        colliderMesh.push_back(v14);

        colliderFaces.reserve(2);
        colliderFaces.push_back(Face(v3,v2,v1));
        colliderFaces.push_back(Face(v3,v2,v4));

        computeInertiaTensor();
    }
}