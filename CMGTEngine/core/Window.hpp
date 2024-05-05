#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include<iostream>
#include<string>
using namespace std;
namespace cmgt
{
	class Window
	{
	private:
		GLFWwindow* window;

		void InitWindow();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	public:
		Window(int Width, int Height, const string& WindowName);
		~Window();

		const int Width;
		const int Height;
		const string windowName;

		bool isOpened();
		void update();
		void close();

		void initVKSurface(VkInstance& instance, VkSurfaceKHR& surface);
		void GetFrameBuffer(int& width, int& height);
		VkExtent2D getWindiwExtend() { return { static_cast<uint32_t>(Width), static_cast<uint32_t>(Height) }; }
	};
}
