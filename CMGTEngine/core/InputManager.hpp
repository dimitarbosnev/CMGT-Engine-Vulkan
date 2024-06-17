#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#pragma once

#include <GLFW/glfw3.h>
#include "config.hpp"
#include "glm.hpp"
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
		static glm::vec2 mousePosition();
		static glm::vec2 deltaMousePosition();
		static bool isMouseMoved();
	};
}
#endif //INPUTMANAGER_HPP