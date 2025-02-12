
#include "physics-engine/MeshCollider.h"
#include "physics-engine/Shape.h"
#include"core/GameObject.h"
namespace cmgt{
    MeshCollider::MeshCollider() : Collider(){}
    MeshCollider::MeshCollider(std::vector<Vertex> meshData) : Collider() {
        populateCollider(meshData);
        _name = "Collider";
        
    }

    void MeshCollider::OnSetOwner(){
        if(colliderMesh.size() == 0 ){
           Mesh* mesh = _owner->getComponent<Mesh>();
           if(mesh != nullptr)
            populateCollider(mesh->getVertexData());
        }

    }
    void MeshCollider::update(float pStep) {
    }

    void MeshCollider::populateCollider(const std::vector<Vertex>& meshData){
        colliderFaces.reserve(meshData.size() / 3);
        for(int i = 0; i < meshData.size(); i+=3){
            colliderFaces.push_back(Face(meshData[i].position, meshData[i+1].position, meshData[i+2].position));
        }

        colliderMesh.reserve(meshData.size());
        for(const Vertex& vert : meshData){
            bool duplicate = false;
            for(const glm::vec3& v : colliderMesh){
                if(v == vert.position){
                    duplicate = true;
                    break;
                }
            }
            if(duplicate) continue;

            colliderMesh.push_back(vert.position);
        }
        colliderMesh.resize(colliderMesh.size());
    }

}