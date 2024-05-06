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
#include "config.hpp"
using namespace std;

namespace cmgt {
	class Game : public Singleton<Game>
	{
	public:
		Game(int Width, int Heigth, string Name);
		~Game();
		void run();
		void exit();

	protected:
		virtual void OnInit() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnExit() = 0;
		Window* gameWindow;
		VulkanInstance* vulkanAPI;
		VulkanSwapchain* vulkanSwapChian;
		VkPipelineLayout pipelineLayout;
		ShaderProgram* shader;
		vector<VkCommandBuffer> commandBuffers;
	private:
		void initEngine();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	};

}
#endif //GAME_HPP