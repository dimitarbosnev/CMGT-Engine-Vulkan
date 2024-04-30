#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#define NOMINMAX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Window.hpp"
#include<cstdlib>
#include<vector>
#include<optional>
#include<set>
#include<algorithm> 
#include<limits>
#include<map>

namespace cmgt {
	 class InstanceAPI {
		private:
			InstanceAPI(const InstanceAPI&) = delete;
			InstanceAPI& operator=(const InstanceAPI&) = delete;
		public:
			InstanceAPI();
			virtual ~InstanceAPI();

			virtual void initAPI() = 0;
			virtual void destroyAPI() = 0;
			virtual const VkDevice& getGPU() = 0;
	};
}