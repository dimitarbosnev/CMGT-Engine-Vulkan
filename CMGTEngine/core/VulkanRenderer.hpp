#ifndef VULKANRENDERER_HPP
#define VULKANRENDERER_HPP

#pragma once
#include "paths.hpp"
#include "config.hpp"
#include<string>
#include<vector>
#include<list>
#include "VulkanInstance.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
using namespace std;

namespace cmgt {
	class VulkanRenderer : public Singleton<VulkanRenderer> {
		public:
			static void InitializeRenderer();
			VulkanRenderer(const VulkanRenderer&) = delete;
			VulkanRenderer& operator=(const VulkanRenderer&) = delete;

			list<Mesh*> meshesToRender;
			static void AddMeshToRender(Mesh* mesh);
			static void RemoveFromRenderer(Mesh* mesh);
		protected:
			
		private:
			VulkanRenderer();
			//void createCommandBuffers();
			//void freeCommandBuffers();
			//void render();
			//void recreateSwapchain();
	};
}
#endif //VULKANRENDERER_HPP