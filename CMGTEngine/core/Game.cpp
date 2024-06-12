#pragma once
#include "Game.hpp"

namespace cmgt {

	Game::Game(int pWidth, int pHeight, string pName) {
		Window::InitializeWindow(pWidth, pHeight, pName);
	}

	Game::~Game() {
		glfwTerminate();
		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		VulkanInstance::InitializeVulkan();
		VulkanSwapchain::InitializeSwapchain(Window::getInstance().getWindowExtend());
		//Hard coded mesh
		vector<Mesh::Vertex> vertecies{ {{0.0f,-0.5f,0.0f}, {1,0,0}},
			{{0.5f,0.5f,0.0f}, {0,1,0}},
			{{-0.5f,0.5f,0.0f},{0,0,1}} };
		//mesh = new Mesh(vertecies);
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
		cout << "Initalizing CMGT Engine Utils...\n";
			ObjectManager::InitializesObjectManager();
			SceneManager::InitializesSceneManager();
		cout << "Utils Initalized!\n";

		cout << "CMGT Engine Initialized!\n";
	}

	void Game::drawFrame() {
		VulkanSwapchain& swapchian = VulkanSwapchain::getInstance();
		uint32_t imageIndex;
		VkResult result = swapchian.acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw runtime_error("failed to accure swap chain image");

		recordCommandBuffer(imageIndex);
		result = swapchian.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || Window::getInstance().isWindowResized()) {
			Window::getInstance().resetWindowResizeFlag();
			recreateSwapchain();
			return;
		}
		if (result != VK_SUCCESS)
			throw runtime_error("failed to present swap chian image!");
	}


	void Game::run() {

		initEngine();
		OnInit();
		OnStart();
		while (!Window::getInstance().isOpened()) {
			OnUpdate();
			OnRender();
			drawFrame();
		}
		exit();
	}

	void Game::exit() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		Window& window = Window::getInstance();
		VulkanSwapchain& swapchain = VulkanSwapchain::getInstance();
		vkDeviceWaitIdle(instance.device());
		OnExit();
		vkDestroyPipelineLayout(instance.device(), pipelineLayout, nullptr);
		//delete mesh;
		delete &SceneManager::getInstance();
		delete &ObjectManager::getInstance();
		delete &window;
		delete shader;
		delete &swapchain;
		delete &instance;

		glfwTerminate();
		cout << "GLFW Terminated!\n";
	}

}
