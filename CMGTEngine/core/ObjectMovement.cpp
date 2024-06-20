#pragma once
#include "ObjectMovement.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
namespace cmgt{

    ObjectMovement::ObjectMovement(float pMoveSpeed = 1, float pRotationSpeed = 1) : _moveSpeed(pMoveSpeed), _rotationSpeed(pRotationSpeed){
    }

    void ObjectMovement::update(float pStep) {
        if (InputManager::isKeyPressed(GLFW_KEY_W)) {
            _owner->Translate(glm::vec3(0, 0, _moveSpeed) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_S)) {
            _owner->Translate(glm::vec3(0, 0, -_moveSpeed) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_A)) {
            _owner->Translate(glm::vec3(-_moveSpeed, 0, 0) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isKeyPressed(GLFW_KEY_D)) {
            _owner->Translate(glm::vec3(_moveSpeed, 0, 0) * pStep);
            cout << _owner->getWorldPosition() << endl;
        }
        if (InputManager::isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
            glm::vec2 deltaPos = InputManager::deltaMousePosition();
            _owner->Rotate(deltaPos.x * pStep * _rotationSpeed, glm::vec3(0, -1, 0));
            _owner->Rotate(deltaPos.y * pStep * _rotationSpeed, glm::vec3(1, 0, 0));
            //cout << "Camera Transform: \n" << _owner->getTransform() << endl;
            cout << "Camera Rotation: \n" << _owner->getTransform() << endl;
        }
        else {
            _owner->Rotate(-pStep, glm::vec3(0, 1, 0));
        }
        //cout << "Delta mouse pos: " << InputManager::deltaMousePosition() << " | Current mouse pos: " << InputManager::mousePosition() << endl;
    }
}