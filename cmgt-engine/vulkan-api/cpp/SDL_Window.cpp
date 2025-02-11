#define SDL_WINDOW_H
#ifndef SDL_WINDOW_H
#include "vulkan-api/SDL_Window.h"
#include <SDL2/SDL_vulkan.h>
namespace cmgt{
    void TEST(){
        //SDL_Vulkan_CreateSurface();
        //SDL_Vulkan_GetInstanceExtensions();
    }

    SDLWindow::SDLWindow(int pWidth, int pHeight, const std::string& pName) : Window(pWidth,pHeight,pName){
        InitWindow();
    }
    SDLWindow::~SDLWindow(){
        FreeWindow();
    }
     void SDLWindow::InitWindow() {
        std::cout << "Initializing Window...\n";
        SDL_Init(SDL_INIT_EVERYTHING);
        
        //SDL_SetHint(SDL_HINT_X, Value); for hints
        
        window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

        //glfwSetWindowAspectRatio(window, 16, 9);
        //glfwSetWindowUserPointer(window, this);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
        SDL_AddEventWatch(resizeWindowCallBack, window);
        std::cout << "Window Initialized!\n";
    }

    int SDLWindow::resizeWindowCallBack(void* data, SDL_Event* event) {
        if(event->type == SDL_WINDOWEVENT_RESIZED && event->type == SDL_WINDOWEVENT_SIZE_CHANGED){
            if(SDLWindow* gameWindow = dynamic_cast<SDLWindow*>(Window::get())){
                int width, height;
                SDL_GetWindowSize(gameWindow->window, &width, &height);
                gameWindow->_resized = true;
                gameWindow->_width = width;
                gameWindow->_height = height;
            }
        } 
        
        return NULL;
    }

    void  SDLWindow::waitEvents(){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
        }
    }

    bool SDLWindow::isOpened() {
        bool shouldClose = false;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                shouldClose = true;
        }
        return shouldClose;
    }

    void SDLWindow::update(){
        //this will use event callback
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
        }
    }

    void SDLWindow::FreeWindow() {
	    SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void SDLWindow::initVKSurface(VkInstance& instance,VkSurfaceKHR& surface) {
        std::cout << "Initialize Surface...\n";
        if (SDL_Vulkan_CreateSurface(window,instance,&surface) != SDL_TRUE) {
            throw std::runtime_error("failed to create window surface!");
        }
        std::cout << "Surface initialized!\n";
    }

    std::vector<const char*> SDLWindow::getInstanceExtentions(){
        uint32_t sdlExtensionCount = 0;
		const char** sdlExtensions;
		SDL_Vulkan_GetInstanceExtensions(window,&sdlExtensionCount,sdlExtensions);

		return std::vector<const char*>(sdlExtensions, sdlExtensions + sdlExtensionCount);
    }
    void SDLWindow::GetFrameBuffer(int &width,int &height) {
        SDL_Vulkan_GetDrawableSize(window, &width, &height);
    }
}
#endif //SDL_WINDOW_H