
#include "physics-engine/PlaneCollider.h"
#include"core/GameObject.h"
namespace cmgt{

    PlaneCollider::PlaneCollider() : Collider() {
        glm::vec3 v1(1,0,1);
        glm::vec3 v2(1,0,-1);
        glm::vec3 v3(-1,0,1);
        glm::vec3 v4(-1,0,-1);

        colliderMesh.reserve(4);
        colliderMesh.push_back(v1);
        colliderMesh.push_back(v2);
        colliderMesh.push_back(v3);
        colliderMesh.push_back(v4);

        colliderFaces.reserve(2);
        colliderFaces.push_back(Face(v1,v2,v3));
        colliderFaces.push_back(Face(v4,v2,v3));
    }
}