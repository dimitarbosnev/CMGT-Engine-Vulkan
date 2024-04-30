#pragma once
#define GLFW_INCLUDE_VULKAN
#define NOMINMAX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Window.hpp"
#include<vector>
#include<optional>
#include<set>
#include<algorithm> 
#include<limits>
#include<map>
#include "VulkanInstance.hpp"
using namespace std;

namespace cmgt {
	class Game
	{
	public:
		Game(int Width, int Heigth, string Name, bool debug = false);
		~Game();
		void run();
		void exit();

	protected:
		virtual void OnInit() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		Window* gameWindow;
		InstanceAPI* gameAPI;
	private:
		void initEngine();
		
		Game(const Game&);
		Game& operator=(const Game&);
	};

}