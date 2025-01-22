#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include "core/config.h"
using namespace std;
namespace cmgt
{
	class Window : public Singleton<Window>
	{
	private:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(int pWidth, int pHeight, const string& pName);

		GLFWwindow* window;

		void InitWindow();
		static void resizeWindowCallBack(GLFWwindow* pWindow, int pWidth, int pHeight);

		int _width;
		int _height;
		bool _resized = false;
	public:
		static void InitializeWindow(int pWidth, int pHeight, const string& pName);
		~Window();

		const string windowName;

		int getKeyState(int keyCode);
		bool isOpened();
		bool isWindowResized() { return _resized; }
		void resetWindowResizeFlag() { _resized = false; }
		void update();
		void close();

		void initVKSurface(VkInstance& instance, VkSurfaceKHR& surface);
		void GetFrameBuffer(int& width, int& height);
		VkExtent2D getWindowExtend() { return { static_cast<uint32_t>(_width), static_cast<uint32_t>(_height) }; }
	};
}
#endif //WINDOW_H