#include "vulkan-api/Window.h"
#include "minimal/log.h"
namespace cmgt{
    Window::Window(int pWidth, int pHeight, const std::string& pName) 
        : Singelton<Window>(this), _width(pWidth), _height(pHeight), windowName(pName) {
        Log::msg("Window Initalized!");
        Log::flush_buffer();
    }

    Window::~Window() {
        Log::msg("Window Destroyed!");
    }

   
}