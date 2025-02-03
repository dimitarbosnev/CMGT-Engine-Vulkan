#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include "vulkan-api/VulkanInstance.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>

namespace cmgt
{
	class Window
	{
		friend class InputManager;
	private:
		Window(const Window&);
		Window& operator=(const Window&);

		GLFWwindow* window;
		VulkanInstance& vkInstnace;
		void InitWindow();
		static void resizeWindowCallBack(GLFWwindow* pWindow, int pWidth, int pHeight);

		int _width;
		int _height;
		bool _resized = false;
	public:
		Window(int pWidth, int pHeight, const std::string& pName, VulkanInstance& instance);
		~Window();

		const std::string windowName;

		int getKeyState(int keyCode);
		bool isOpened();
		bool isWindowResized() { return _resized; }
		void resetWindowResizeFlag() { _resized = false; }
		void update();
		void close();
		void initVKSurface(VkInstance instance, VkSurfaceKHR surface);
		void GetFrameBuffer(int& width, int& height);
		VkExtent2D getWindowExtend() { return { static_cast<uint32_t>(_width), static_cast<uint32_t>(_height) }; }
	};
}
#endif //WINDOW_H