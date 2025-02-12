
#include "utils/MouseMovement.h"
#include "core/GameObject.h"
#include "core/Globals.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    MouseMovement::MouseMovement(){
    }

    void MouseMovement::update(float pStep) {
        glm::vec3 dir = SceneManager::get()->getCurrentScene()->getWorld()->getMainCamera()->viewportToWorld(Input::mousePosition());

        getTransform().setWorldPosition(dir*10);
    }
}