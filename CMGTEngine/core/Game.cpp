#pragma once
#include "Game.hpp"
#include "glm.hpp"
#include "Camera.hpp"
#include "VulkanRenderer.hpp"
#include "Scene.hpp"
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
		//createPipelineLayout();
		//createPipeline();
		//createCommandBuffers();

		cout << "Initalizing CMGT Engine Utils...\n";
			ObjectManager::InitializesObjectManager();
			SceneManager::InitializesSceneManager();
			VulkanRenderer::InitializeRenderer();
		cout << "Utils Initalized!\n";

		cout << "CMGT Engine Initialized!\n";

	}

	void Game::recreateSwapchain() {
		Window& window = Window::getInstance();
		auto extent = window.getWindowExtend();
		while (extent.width == 0 || extent.height == 0) {
			extent = window.getWindowExtend();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(VulkanInstance::getInstance().device());


		VulkanSwapchain::RecreateSwapchain(extent);
		if (VulkanSwapchain::getInstance().imageCount() != commandBuffers.size()) {
			freeCommandBuffers();
			createCommandBuffers();
		}
		createPipeline();
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
		float lastTick = glfwGetTime();
		float second = 0;
		float fps = 0;
		while (!Window::getInstance().isOpened()) {
			double time = glfwGetTime();
			_deltaTime = (float)time - lastTick;
			lastTick = (float)time;
			if (second >= 1)
			{
				cout << "FPS: " << fps << endl;
				second = 0;
				fps = 0;
			}
			else {
				second += _deltaTime;
				fps++;
			}
			OnUpdate();
			SceneManager::update(_deltaTime);
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
		delete pipeline;
		SceneManager::destroyInstance();
		ObjectManager::destroyInstance();
		Window::destroyInstance();
		VulkanRenderer::destroyInstance();
		VulkanSwapchain::destroyInstance();
		VulkanInstance::destroyInstance();

		glfwTerminate();
		cout << "GLFW Terminated!\n";
	}

}
