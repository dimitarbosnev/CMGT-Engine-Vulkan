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
	class VukanRenderer : public Singleton<VukanRenderer> {
		public:
			static void InitializeRenderer();
			VukanRenderer(const VukanRenderer&) = delete;
			VukanRenderer& operator=(const VukanRenderer&) = delete;

			list<Mesh*> meshesToRender;
			static void AddMeshToRender(Mesh& mesh);
			static Camera& getCamera();
		protected:
			
		private:
			VukanRenderer();
			//void createCommandBuffers();
			//void freeCommandBuffers();
			//void render();
			//void recreateSwapchain();
	};
}
#endif //VULKANRENDERER_HPP