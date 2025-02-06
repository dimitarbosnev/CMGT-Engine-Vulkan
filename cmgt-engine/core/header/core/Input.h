#ifndef INPUT_H
#define INPUT_H

#pragma once
#include "vulkan-api/GLFW_Window.h"
#include "minimal/glm.h"
#include "minimal/types.h"
namespace cmgt
{
	//Input class should be revisited for now it will only work wit GLFW_Window
	class Input
	{
	private:
		inline static GLFWwindow* window = nullptr;
		inline static glm::vec2 _previousMousePosition = glm::vec2(0);
	public:
		Input() = delete;
		~Input() = delete;
		static void InitInput();
		static void processInput();
		static bool isKeyPressed(int);
		static bool isMousePressed(int);
		static glm::vec2 mousePosition();
		static glm::vec2 deltaMousePosition();
		static bool isMouseMoved();
	};
}
#endif //INPUT_H