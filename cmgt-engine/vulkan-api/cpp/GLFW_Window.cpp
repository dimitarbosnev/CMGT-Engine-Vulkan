
#include "vulkan-api/GLFW_Window.h"
namespace cmgt{
    GLFWindow::GLFWindow(int pWidth, int pHeight, const std::string& pName) : Window(pWidth,pHeight,pName){
        InitWindow();
    }
     GLFWindow::~GLFWindow(){
        FreeWindow();
     }
     void GLFWindow::InitWindow() {
        std::cout << "Initializing Window...\n";
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);

        window = glfwCreateWindow(_width, _height, windowName.c_str(), nullptr,nullptr);
        glfwSetWindowAspectRatio(window, 16, 9);
        glfwSetWindowUserPointer(window, this);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
        std::cout << "Window Initialized!\n";
    }

    void GLFWindow::resizeWindowCallBack(GLFWwindow* pWindow, int pWidth, int pHeight) {
        auto window = reinterpret_cast<GLFWindow*>(glfwGetWindowUserPointer(pWindow));
        window->_resized = true;
        window->_width = pWidth;
        window->_height = pHeight;
    }

    void  GLFWindow::waitEvents(){
        glfwWaitEvents();
    }

    bool GLFWindow::isOpened() {
        glfwPollEvents();
        return  glfwWindowShouldClose(window);
    }

    void GLFWindow::update(){
        //this will use event call back
    }

    void GLFWindow::FreeWindow() {
        //InputManager::destroyInstance();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void GLFWindow::initVKSurface(VkInstance& instance,VkSurfaceKHR& surface) {
        std::cout << "Initialize Surface...\n";
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
        std::cout << "Surface initialized!\n";
    }
    std::vector<const char*> GLFWindow::getInstanceExtentions(){
        uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
    }

    void GLFWindow::GetFrameBuffer(int &width,int &height) {
        glfwGetFramebufferSize(window, &width, &height);
    }
}