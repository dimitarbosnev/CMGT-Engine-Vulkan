#include "Window.hpp"

namespace cmgt{

    Window::Window(int Width, int Height, string Name) : _width(Width), _height(Height), windowName(Name) {
        InitWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
        cout << "Window destroyed\n";
    }

    void Window::InitWindow() {
        cout << "Initializing Window...\n";
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

        window = glfwCreateWindow(_width, _height, windowName.c_str(),nullptr,nullptr);
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