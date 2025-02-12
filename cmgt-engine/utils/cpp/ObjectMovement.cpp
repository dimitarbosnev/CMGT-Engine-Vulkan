
#include "utils/ObjectMovement.h"
#include "core/GameObject.h"
#include "core/Globals.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    ObjectMovement::ObjectMovement(float pMoveSpeed, float pRotationSpeed) : _moveSpeed(pMoveSpeed), _rotationSpeed(pRotationSpeed){
    }

    void ObjectMovement::update(float pStep) {
        glm::mat4 worldPos = getTransform().getWorldTransform();
        if (Input::isKeyPressed(GLFW_KEY_W)) {
            _owner->getTransform().Translate(glm::vec3(0, 0, _moveSpeed) * pStep);
            std::cout << worldPos[3] << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_S)) {
            _owner->getTransform().Translate(glm::vec3(0, 0, -_moveSpeed) * pStep);
            std::cout << worldPos[3] << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_A)) {
            _owner->getTransform().Translate(glm::vec3(-_moveSpeed, 0, 0) * pStep);
            std::cout << worldPos[3] << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_D)) {
            _owner->getTransform().Translate(glm::vec3(_moveSpeed, 0, 0) * pStep);
            std::cout <<worldPos[3] << std::endl;
        }
        if (Input::isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
            glm::vec2 deltaPos = Input::deltaMousePosition();
            _owner->getTransform().Rotate(deltaPos.x * pStep * _rotationSpeed, glm::vec3(0, -1, 0));
            _owner->getTransform().Rotate(deltaPos.y * pStep * _rotationSpeed, glm::vec3(1, 0, 0));
            //cout << "Camera Transform: \n" << _owner->getTransform() << endl;
            //cout << "Camera Rotation: \n" << _owner->getTransform() << endl;
        }
        else {
            _owner->getTransform().Rotate(-pStep, glm::vec3(0, 1, 0));
        }
        RayInfo info;
            if(PhysicsEngine::rayCast(worldPos[3], getTransform().getLocalRotationMatrix() * glm::vec3(-1, 0, 0),&info))
                std::cout << "RayCast WORKS!!!" << std::endl;
        //cout << "Delta mouse pos: " << InputManager::deltaMousePosition() << " | Current mouse pos: " << InputManager::mousePosition() << endl;
    }
}