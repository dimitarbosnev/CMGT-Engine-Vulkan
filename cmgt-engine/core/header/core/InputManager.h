#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma once

#include <GLFW/glfw3.h>
#include "minimal/glm.h"
namespace cmgt
{
	class InputManager
	{
	private:

		InputManager(const InputManager&);
		InputManager& operator=(const InputManager&);
		GLFWwindow* window;
		glm::vec2 _previousMousePosition;
	public:
		InputManager(GLFWwindow* window);
		~InputManager();
		void updateInputManager();
		bool isKeyPressed(int);
		bool isMousePressed(int);
		glm::vec2 mousePosition();
		glm::vec2 deltaMousePosition();
		bool isMouseMoved();
	};
}
#endif //INPUTMANAGER_H