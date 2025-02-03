
#include "core/InputManager.h"
namespace cmgt{
    
    InputManager::InputManager(Window& pWindow) : window(pWindow.window) {}

    InputManager::~InputManager(){}

    void InputManager::updateInputManager()
    {
        _previousMousePosition = mousePosition();
    }


    bool InputManager::isKeyPressed(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool InputManager::isMousePressed(int button)
    {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    glm::vec2 InputManager::mousePosition()
    {
        double x, y;
       glfwGetCursorPos(window, &x, &y);
       return glm::vec2(x, y);
    }

    glm::vec2 InputManager::deltaMousePosition()
    {
        return  mousePosition() - _previousMousePosition;
    }

    bool InputManager::isMouseMoved()
    {
        return glm::length(deltaMousePosition()) > 0;
    }

}