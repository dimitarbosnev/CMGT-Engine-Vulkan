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

		cout << "Initalizing CMGT Engine Utils...\n";
			ObjectManager::InitializesObjectManager();
			SceneManager::InitializesSceneManager();
			VulkanRenderer::InitializeRenderer();
		cout << "Utils Initalized!\n";

		cout << "CMGT Engine Initialized!\n";

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
			VulkanRenderer::render();
		}
		exit();
	}

	void Game::exit() {
		VulkanInstance& instance = VulkanInstance::getInstance();
		Window& window = Window::getInstance();
		VulkanSwapchain& swapchain = VulkanSwapchain::getInstance();
		vkDeviceWaitIdle(instance.device());
		OnExit();
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
