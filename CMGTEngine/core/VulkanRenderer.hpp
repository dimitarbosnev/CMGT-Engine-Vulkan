#ifndef VULKANRENDERER_HPP
#define VULKANRENDERER_HPP

#pragma once
#include "paths.hpp"
#include<string>
#include<vector>
#include "VulkanInstance.hpp"
using namespace std;

namespace cmgt {
	class VukanRenderer {
		public:
			VukanRenderer(const VukanRenderer&) = delete;
			VukanRenderer& operator=(const VukanRenderer&) = delete;
		private:
			void createCommandBuffers();
			void freeCommandBuffers();
			void render();
			void recreateSwapchain();
	};
}
#endif //VULKANRENDERER_HPP