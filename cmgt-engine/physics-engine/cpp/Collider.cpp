
#include "physics-engine/Collider.h"
#include "core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    Collider::Collider(std::vector<Vertex> meshData) {
        colliderMesh = meshData;
        _name = "Collider";
        PhysicsEngine::get()->addCollider(this);
    }


    void Collider::update(float pStep) {
    }
}