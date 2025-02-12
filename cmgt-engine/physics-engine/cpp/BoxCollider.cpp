
#include "physics-engine/BoxCollider.h"
#include"core/GameObject.h"
namespace cmgt{

    BoxCollider::BoxCollider() : Collider() {
        glm::vec3 v1(1, -1, 1); //1
        glm::vec3 v2(1,1,1); //2
        glm::vec3 v3(1,-1,-1); //3
        glm::vec3 v4(1,1,-1); //4
        glm::vec3 v5(-1,-1,1); //5
        glm::vec3 v6(-1,1,1); //6
        glm::vec3 v7(-1,-1,-1); //7
        glm::vec3 v8(-1,1,-1); //8

        colliderMesh.reserve(8);
        colliderMesh.push_back(v1);
        colliderMesh.push_back(v2);
        colliderMesh.push_back(v3);
        colliderMesh.push_back(v4);
        colliderMesh.push_back(v5);
        colliderMesh.push_back(v6);
        colliderMesh.push_back(v7);
        colliderMesh.push_back(v8);

        colliderFaces.reserve(12);
        colliderFaces.push_back(Face(v5,v3,v1));
        colliderFaces.push_back(Face(v3,v8,v4));

        colliderFaces.push_back(Face(v7,v6,v8));
        colliderFaces.push_back(Face(v2,v8,v6));

        colliderFaces.push_back(Face(v1,v4,v2));
        colliderFaces.push_back(Face(v5,v2,v6));

        colliderFaces.push_back(Face(v5,v7,v3));
        colliderFaces.push_back(Face(v3,v7,v8));

        colliderFaces.push_back(Face(v7,v5,v6));
        colliderFaces.push_back(Face(v2,v4,v8));

        colliderFaces.push_back(Face(v1,v3,v4));
        colliderFaces.push_back(Face(v5,v1,v2));


    }


    void BoxCollider::update(float pStep) {
    }
}