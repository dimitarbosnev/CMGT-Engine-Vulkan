#pragma once
#define GLFW_INCLUDE_VULKAN
#define NOMINMAX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include<cstdlib>
#include<vector>
#include<optional>
#include<set>
#include<algorithm> 
#include<limits>
#include<map>
#include "Window.hpp"
#include "InstanceAPI.hpp"
namespace cmgt {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};
	class VulkanInstance : public InstanceAPI{
	private:
		void initVulkan();
		void initDebugMsg();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void initPhysicalDevice();
		void initLogicalDevice();
		void initSwapChain();
		void initImageViews();
		void createGraphicsPipeline();
		bool isDeviceSuitable(VkPhysicalDevice device, SwapChainSupportDetails swapChainSupport);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		int deviceScore(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		vector<const char*> getRequiredExtensions();
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		const vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
		bool checkValidationLayerSupport();

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
			cerr << "validation layer: " << pCallbackData->pMessage << endl;

			return VK_FALSE;
		}

		VkInstance _vulkan;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkSurfaceKHR surface;
		VkSwapchainKHR swapChain;
		VkDebugUtilsMessengerEXT _debugMsg;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		Window* window;
		const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		QueueFamilyIndices familyQueue;
		VulkanInstance(const VulkanInstance&) = delete;
		VulkanInstance& operator=(const VulkanInstance&) = delete;
	public:
		const bool _enableValidationLayers;
		void initAPI() override;
		void destroyAPI() override;
		const VkDevice& getGPU() override;

		VulkanInstance(Window& win,bool validationLayers);
		~VulkanInstance();
	};
}