
#include "core/Input.h"
namespace cmgt{
    
    
    void Input::InitInput(){
        GLFWindow* gameWindow = dynamic_cast<GLFWindow*>(Window::get());
        window = gameWindow->window;
    }
    void Input::processInput()
    {
        _previousMousePosition = mousePosition();
    }

    bool Input::isKeyPressed(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::isMousePressed(int button)
    {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    glm::vec2 Input::mousePosition()
    {
        double x, y;
       glfwGetCursorPos(window, &x, &y);
       return glm::vec2(x, y);
    }

    glm::vec2 Input::deltaMousePosition()
    {
        return  mousePosition() - _previousMousePosition;
    }

    bool Input::isMouseMoved()
    {
        return glm::length(deltaMousePosition()) > 0;
    }

}