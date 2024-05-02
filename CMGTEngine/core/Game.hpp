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
#include "Window.hpp"
#include "VulkanInstance.hpp"
#include  "VulkanSwapchain.hpp"
using namespace std;

namespace cmgt {
	class Game
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
		Window* gameWindow;
		VulkanInstance* vulkanAPI;
		VulkanSwapchain* vulkanSwapChian;
		VkPipelineLayout pipelineLayout;
		vector<VkCommandBuffer> commandBuffers;
	private:
		void initEngine();
		void createPipelineLayout();
		void createPipeline();
		void createFrameBufferCommands();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	};

}