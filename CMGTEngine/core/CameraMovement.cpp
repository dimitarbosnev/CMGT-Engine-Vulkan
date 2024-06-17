#pragma once
#include "CameraMovement.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
namespace cmgt{

    CameraMovement::CameraMovement() {
    }

    void CameraMovement::update(float pStep) {
        if (InputManager::isKeyPressed(GLFW_KEY_UP)) {
            _owner->Translate(glm::vec3(0, 0, 10) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_DOWN)) {
            _owner->Translate(glm::vec3(0, 0, -10) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_LEFT)) {
            _owner->Translate(glm::vec3(-10, 0, 0) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_RIGHT)) {
            _owner->Translate(glm::vec3(10, 0, 0) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isMouseMoved()) {
            glm::vec2 deltaPos = InputManager::deltaMousePosition();
            _owner->Rotate(deltaPos.y, glm::vec3(-1, 0, 0));
            _owner->Rotate(deltaPos.x, glm::vec3(0, 1, 0));
            cout << "Camera Transform: " << _owner->getTransform() << endl;
        }
        //cout << "Delta mouse pos: " << InputManager::deltaMousePosition() << " | Current mouse pos: " << InputManager::mousePosition() << endl;
    }
}