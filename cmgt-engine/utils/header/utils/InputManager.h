#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma once

#include <GLFW/glfw3.h>
#include "core/config.h"
#include "core/glm.h"
using namespace std;
namespace cmgt
{
	class InputManager : public Singleton<InputManager>
	{
	private:

		InputManager(const InputManager&);
		InputManager& operator=(const InputManager&);
		InputManager(GLFWwindow*);

		GLFWwindow* window;
		glm::vec2 _previousMousePosition;
	public:
		static void InitializeInputManager(GLFWwindow*);
		~InputManager();
		static void updateInputManager();
		static bool isKeyPressed(int);
		static bool isMousePressed(int);
		static glm::vec2 mousePosition();
		static glm::vec2 deltaMousePosition();
		static bool isMouseMoved();
	};
}
#endif //INPUTMANAGER_H