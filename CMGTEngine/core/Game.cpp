#include "Game.hpp"


namespace cmgt {
	Game::Game(int Width,int Height,string Name) {
		
		gameWindow = new Window(Width, Height, Name);
		
	}

	Game::~Game() {
		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		vulkanAPI = new VulkanInstance(*gameWindow);
		vulkanSwapChian = new VulkanSwapchain(*vulkanAPI, gameWindow->getWindiwExtend());
		cout << "CMGT Engine Initialized!\n";
	}

	void Game::run() {
		initEngine();
		OnInit();
		OnStart();
		while (!gameWindow->isOpened()) {
			gameWindow->update();
			OnUpdate();
			OnRender();
		}
		exit();
	}

	void Game::exit() {
		gameWindow->close();
		delete gameWindow;
		delete vulkanAPI;
	}

}
