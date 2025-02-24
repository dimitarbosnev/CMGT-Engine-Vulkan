
#include "vulkan-api/GLFW_Window.h"
#include "minimal/log.h"
namespace cmgt{
    GLFWindow::GLFWindow(int pWidth, int pHeight, const std::string& pName) : Window(pWidth,pHeight,pName){
        InitWindow();
    }
     GLFWindow::~GLFWindow(){
        FreeWindow();
     }
     void GLFWindow::InitWindow() {
        Log::msg("Initializing Window...");
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);

        window = glfwCreateWindow(_width, _height, windowName.c_str(), nullptr,nullptr);
        glfwSetWindowAspectRatio(window, 16, 9);
        glfwSetWindowUserPointer(window, this);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
        Log::msg("Window Initialized!");

        Log::flush_buffer();
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

    void GLFWindow::close(){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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
        Log::msg("Initialize Surface...");
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error(Log::error_critical("failed to create window surface!"));
        }
        Log::msg("Surface initialized!");
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