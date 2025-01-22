#ifndef GAME_H
#define GAME_H

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
#include "core/Window.h"
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanSwapchain.h"
#include "core/ShaderProgram.h"
#include "core/BasicShaderProgram.h"
#include "core/ObjectManager.h"
#include "core/SceneManager.h"
#include "core/config.h"
#include "utils/Mesh.h"
#include "render-engine/VulkanRenderer.h"
#include "core/GraphicsPipeline.h"
using namespace std;

namespace cmgt {
	class Game
	{
	public:
		Game(int pWidth, int pHeigth, string pName);
		virtual ~Game();
		void run();
		void exit();
		float GetDeltaTime() { return _deltaTime; }
	protected:
		virtual void OnInit() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnExit() = 0;
	private:
		float _deltaTime;
		void initEngine();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	};

}
#endif //GAME_H