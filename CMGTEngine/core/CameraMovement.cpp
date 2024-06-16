#pragma once
#include "CameraMovement.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
namespace cmgt{

    CameraMovement::CameraMovement() {
    }

    void CameraMovement::update(float pStep) {
        if (InputManager::isKeyPressed(GLFW_KEY_UP))
            cout << "up pressed" << endl;
    }
}