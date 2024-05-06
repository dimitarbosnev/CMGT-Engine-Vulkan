#pragma once
#include "Window.hpp"

namespace cmgt{
    Window::Window(int pWidth, int pHeight, const string& pName) : Width(pWidth), Height(pHeight), windowName(pName) {
        InitWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        cout << "WINDOW DESTROYED\n";
    }

    void Window::InitWindow() {
        cout << "Initializing Window...\n";
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

        window = glfwCreateWindow(Width, Height, windowName.c_str(),nullptr,nullptr);
        cout << "Window Initialized!\n";
    }

    bool Window::isOpened() {
        return  glfwWindowShouldClose(window);
    }

    void Window::update() {
            glfwPollEvents();
    }

    void Window::close() {
        glfwDestroyWindow(window);
        cout << "Window closed!\n";
        glfwTerminate();
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