
#include "core/Window.h"
namespace cmgt{
    Window::Window(int pWidth, int pHeight, const std::string& pName, VulkanInstance& instance) 
        : _width(pWidth), _height(pHeight), windowName(pName) {
        InitWindow();
        initVKSurface(instance.instance(),instance.surface());
        //InputManager::InitializeInputManager(window);
    }


    Window::~Window() {
        close();
        std::cout << "Window Destroyed!\n";
    }

    void Window::InitWindow() {
        std::cout << "Initializing Window...\n";
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);

        window = glfwCreateWindow(_width, _height, windowName.c_str(), nullptr,nullptr);
        glfwSetWindowAspectRatio(window, 16, 9);
        glfwSetWindowUserPointer(window, this);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
        std::cout << "Window Initialized!\n";
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
            //InputManager::updateInputManager();
            glfwPollEvents();
    }

    void Window::close() {
        //InputManager::destroyInstance();
        glfwDestroyWindow(window);
    }

    int Window::getKeyState(int keyCode)
    {
        return glfwGetKey(window, keyCode);
    }

    void Window::initVKSurface(VkInstance instance,VkSurfaceKHR surface) {
        std::cout << "Initialize Surface...\n";
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
        std::cout << "Surface initialized!\n";
    }

    void Window::GetFrameBuffer(int &width,int &height) {
        glfwGetFramebufferSize(window, &width, &height);
    }
}