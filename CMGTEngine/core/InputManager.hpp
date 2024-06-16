#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#pragma once

#include <GLFW/glfw3.h>
#include "config.hpp"
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
	public:
		static void InitializeInputManager(GLFWwindow*);
		~InputManager();

		static bool isKeyPressed(int);
	};
}
#endif //INPUTMANAGER_HPP