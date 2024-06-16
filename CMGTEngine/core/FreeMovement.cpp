#pragma once
#include "FreeMovement.hpp"
#include <GLFW/glfw3.h>
#include "Window.hpp"
#include"GameObject.hpp"
namespace cmgt{

    FreeMovment::FreeMovment() {
    }


    void FreeMovment::update(float pStep) {
		Window& window = Window::getInstance();
		if(window.getKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
			_owner->Translate(glm::vec3(0, 0, 40) * pStep);
		}
		if (window.getKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
			_owner->Translate(glm::vec3(0, 0, -40) * pStep);
		}
		if (window.getKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			_owner->Translate(glm::vec3(40, 0, 0) * pStep);
		}
		if (window.getKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
			_owner->Translate(glm::vec3(-40, 0, 0) * pStep);
		}
		cout<<_owner->getLocalPosition()<<endl;
    }
}