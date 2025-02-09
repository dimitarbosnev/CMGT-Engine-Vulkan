
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
        //Some meshes have duplicate vertecies
        //So we check if the vertex is already added
        for(const Vertex& vert : meshData){
            bool duplicate = false;
            for(const glm::vec3& v : colliderMesh){
                if(vert.position == v){
                    duplicate = true;
                    break;
                }
            }
            //if vert is a duplicate we skip it
            if(duplicate) continue;
            colliderMesh.push_back(vert.position);
        }
    }

}