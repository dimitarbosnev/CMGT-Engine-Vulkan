#pragma once
#include "Window.hpp"

namespace cmgt{
    void Window::InitializeWindow(int pWidth, int pHeight, const string& pName) 
    { assignInstance(new Window(pWidth, pHeight, pName)); }  

    Window::Window(int pWidth, int pHeight, const string& pName) 
        : _width(pWidth), _height(pHeight), windowName(pName) {
        InitWindow();
    }


    Window::~Window() {
        close();
        cout << "Window Destroyed!\n";
    }

    void Window::InitWindow() {
        cout << "Initializing Window...\n";
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);

        window = glfwCreateWindow(_width, _height, windowName.c_str(), nullptr,nullptr);
        //glfwSetWindowAspectRatio(window, 16, 9);
        glfwSetWindowUserPointer(window, this);

        glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
        cout << "Window Initialized!\n";
    }

    void Window::resizeWindowCallBack(GLFWwindow* pWindow, int pWidth, int pHeight) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow));
       window->_resized = true;
       window->_width = pWidth;
       window->_height = pHeight;
    }

    bool Window::isOpened() {
        update();
        return  glfwWindowShouldClose(window);
    }

    void Window::update() {
            glfwPollEvents();
    }

    void Window::close() {
        glfwDestroyWindow(window);
    }

    int Window::getKeyState(int keyCode)
    {
        return glfwGetKey(window, keyCode);
    }

    void Window::initVKSurface(VkInstance& instance,VkSurfaceKHR& surface) {
        cout << "Initialize Surface...\n";
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
        cout << "Surface initialized!\n";
    }

    void Window::GetFrameBuffer(int &width,int &height) {
        glfwGetFramebufferSize(window, &width, &height);
    }
}