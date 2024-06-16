#pragma once
#include "InputManager.hpp"

namespace cmgt{
    void InputManager::InitializeInputManager(GLFWwindow* pWindow) { assignInstance(new InputManager(pWindow)); }

    InputManager::~InputManager(){}

    InputManager::InputManager(GLFWwindow* pWindow) : window(pWindow) {}

    bool InputManager::isKeyPressed(int key) {
        return glfwGetKey(getInstance().window, key) == GLFW_PRESS;
    }

}