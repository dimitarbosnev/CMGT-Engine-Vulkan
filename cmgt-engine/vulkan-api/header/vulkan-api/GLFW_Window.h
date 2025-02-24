#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#pragma once
#include "minimal/types.h"
#include "vulkan-api/Window.h"
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define GLFW_EXPOSE_NATIVE_WIN32

namespace cmgt
{
	class GLFWindow : public Window
	{
		friend class Input;
	private:
		GLFWwindow* window;
		static void resizeWindowCallBack(GLFWwindow* pWindow, int pWidth, int pHeight);
		void InitWindow() override;
		void FreeWindow() override;
		void update() override;

	public:
		GLFWindow(int pWidth, int pHeight, const std::string& pName);
		~GLFWindow();
		void waitEvents() override;
		bool isOpened() override;
		void close() override;
		void initVKSurface(VkInstance& instance, VkSurfaceKHR& surface) override;
		std::vector<const char*> getInstanceExtentions() override;
		void GetFrameBuffer(int& width, int& height) override;
	};
}
#endif //GLFW_WINDOW_H