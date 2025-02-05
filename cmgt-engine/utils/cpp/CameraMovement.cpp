
#include "utils/CameraMovement.h"
#include "core/GameObject.h"
#include "core/Globals.h"
namespace cmgt{

    CameraMovement::CameraMovement(float pMoveSpeed, float pRotationSpeed) : _moveSpeed(pMoveSpeed), _rotationSpeed(pRotationSpeed){
    }

    void CameraMovement::update(float pStep) {
        if (Input::isKeyPressed(GLFW_KEY_UP)) {
            _owner->Translate(glm::vec3(0, 0, -_moveSpeed) * pStep);
            std::cout << _owner->getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
            _owner->Translate(glm::vec3(0, 0, _moveSpeed) * pStep);
            std::cout << _owner->getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
            _owner->Translate(glm::vec3(-_moveSpeed, 0, 0) * pStep);
            std::cout << _owner->getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
            _owner->Translate(glm::vec3(_moveSpeed, 0, 0) * pStep);
            std::cout << _owner->getWorldPosition() << std::endl;
        }
        if (Input::isMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            glm::vec2 deltaPos = Input::deltaMousePosition();
            _owner->Rotate(deltaPos.x * pStep * _rotationSpeed, glm::vec3(0, -1, 0));
            _owner->Rotate(deltaPos.y * pStep * _rotationSpeed, glm::vec3(1, 0, 0));
            //cout << "Camera Transform: \n" << _owner->getTransform() << endl;
            //cout << "Camera Rotation: \n" << currentRotation << endl;
        }
        //cout << "Delta mouse pos: " << InputManager::deltaMousePosition() << " | Current mouse pos: " << InputManager::mousePosition() << endl;
    }
}