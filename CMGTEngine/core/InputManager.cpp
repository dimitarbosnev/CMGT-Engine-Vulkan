#pragma once
#include "InputManager.hpp"

namespace cmgt{
    void InputManager::InitializeInputManager(GLFWwindow* pWindow) { assignInstance(new InputManager(pWindow)); }

    InputManager::~InputManager(){}

    void InputManager::updateInputManager()
    {
        getInstance()._previousMousePosition = mousePosition();
    }

    InputManager::InputManager(GLFWwindow* pWindow) : window(pWindow) {}

    bool InputManager::isKeyPressed(int key) {
        return glfwGetKey(getInstance().window, key) == GLFW_PRESS;
    }

    bool InputManager::isMousePressed(int button)
    {
        return glfwGetMouseButton(getInstance().window, button) == GLFW_PRESS;
    }

    glm::vec2 InputManager::mousePosition()
    {
        double x, y;
       glfwGetCursorPos(getInstance().window, &x, &y);
       return glm::vec2(x, y);
    }

    glm::vec2 InputManager::deltaMousePosition()
    {
        return  mousePosition() - getInstance()._previousMousePosition;
    }

    bool InputManager::isMouseMoved()
    {
        return glm::length(deltaMousePosition()) > 0;
    }

}