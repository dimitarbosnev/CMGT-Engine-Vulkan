#include "Game.hpp"


namespace cmgt {
	Game::Game(int Width,int Height,string Name,bool debug) {
		
		gameWindow = new Window(Width, Height, Name);
		gameAPI = new VulkanInstance(*gameWindow, debug);
	}

	Game::~Game() {
		cout << "Game destroyed\n";
	}

	void Game::initEngine() {
		cout << "Initializing CMGT Engine...\n";
		gameAPI->initAPI();
		cout << "CMGT Engine Initialized!\n";
	}

	void Game::run() {
		initEngine();
		OnInit();
		OnStart();
		gameWindow->update();

		exit();
	}

	void Game::exit() {
		gameAPI->destroyAPI();
		gameWindow->close();
		delete gameWindow;
		delete gameAPI;
	}

}
