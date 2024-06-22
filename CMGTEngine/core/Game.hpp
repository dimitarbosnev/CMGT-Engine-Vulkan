#ifndef GAME_HPP
#define GAME_HPP

#pragma once
#define GLFW_INCLUDE_VULKAN
#define NOMINMAX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include<vector>
#include<optional>
#include<set>
#include<algorithm> 
#include<limits>
#include<map>
#include<array>
#include "Window.hpp"
#include "VulkanInstance.hpp"
#include "VulkanSwapchain.hpp"
#include "ShaderProgram.hpp"
#include "BasicShaderProgram.hpp"
#include "ObjectManager.hpp"
#include "SceneManager.hpp"
#include "config.hpp"
#include "Mesh.hpp"
#include "VulkanRenderer.hpp"
#include "GraphicsPipeline.hpp"
using namespace std;

namespace cmgt {
	class Game
	{
	public:
		Game(int pWidth, int pHeigth, string pName);
		~Game();
		void run();
		void exit();
		float GetDeltaTime() { return _deltaTime; }
	protected:
		virtual void OnInit() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnExit() = 0;
		GraphicsPipeline* pipeline;
	private:
		float _deltaTime;
		void initEngine();
		void recreateSwapchain();
		void drawFrame();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	};

}
#endif //GAME_HPP