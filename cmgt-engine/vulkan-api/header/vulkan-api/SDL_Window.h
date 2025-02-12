
/*#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#pragma once
#include "minimal/types.h"
#include "vulkan-api/Window.h"
#include <vulkan/vulkan_core.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#define GLFW_EXPOSE_NATIVE_WIN32

namespace cmgt
{
	class SDLWindow : public Window
	{
		friend class Input;
	private:
		SDL_Window* window;
		//check how to do resize call back on sdl
		static int resizeWindowCallBack(void* data, SDL_Event* event);
		void InitWindow() override;
		void FreeWindow() override;
		void update() override;

	public:
		SDLWindow(int pWidth, int pHeight, const std::string& pName);
		~SDLWindow();
		void waitEvents() override;
		bool isOpened() override;
		void initVKSurface(VkInstance& instance, VkSurfaceKHR& surface) override;
		std::vector<const char*> getInstanceExtentions() override;
		void GetFrameBuffer(int& width, int& height) override;
	};
}
#endif //SDL_WINDOW_H*/