
#include "vulkan-api/Window.h"
namespace cmgt{
    Window::Window(int pWidth, int pHeight, const std::string& pName) 
        : Singelton<Window>(this), _width(pWidth), _height(pHeight), windowName(pName) {
        std::cout << "Window Initalized!\n";
    }

    Window::~Window() {
        std::cout << "Window Destroyed!\n";
    }

   
}