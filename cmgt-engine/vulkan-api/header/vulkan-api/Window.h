#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include "minimal/types.h"
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <string>

#define GLFW_EXPOSE_NATIVE_WIN32

namespace cmgt
{
	class Window : public Singelton<Window>
	{
	private:
		Window(const Window&);
		Window& operator=(const Window&);
	protected:
		int _width;
		int _height;
		bool _resized = false;
		virtual void InitWindow() = 0;
		virtual void FreeWindow() = 0;
	public:
		Window(int pWidth, int pHeight, const std::string& pName);
		virtual ~Window();

		const std::string windowName;


		void resetWindowResizeFlag() { _resized = false; }
		bool isWindowResized() { return _resized; }
		VkExtent2D getWindowExtend() { return { static_cast<uint32_t>(_width), static_cast<uint32_t>(_height) }; }
		virtual void waitEvents() = 0;
		virtual bool isOpened() = 0;
		virtual void update() = 0;
		virtual void close() = 0;
		virtual void initVKSurface(VkInstance& instance, VkSurfaceKHR& surface) = 0;
		virtual std::vector<const char*> getInstanceExtentions() = 0;
		virtual void GetFrameBuffer(int& width, int& height) = 0;
	};
}
#endif //WINDOW_H