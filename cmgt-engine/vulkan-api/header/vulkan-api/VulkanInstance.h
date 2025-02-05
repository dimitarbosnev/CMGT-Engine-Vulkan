#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#pragma once
#include "vulkan-api/Window.h"
#include "minimal/types.h"
#include<vulkan/vulkan.h>
#include<vector>

#define NOMINMAX

namespace cmgt {

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDevice device, VkQueue queue, VkCommandPool commandPool);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount, VkDevice device, VkQueue queue, VkCommandPool commandPool);
	void createImageWithInfo(const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VkPhysicalDevice physicalDevice, VkDevice device);

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct QueueFamilyIndices {
		uint32_t graphicsFamily;
		uint32_t presentFamily;
		bool graphicsFamilyHasValue = false;
		bool presentFamilyHasValue = false;
		bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
	};


	class VulkanInstance : public Singelton<VulkanInstance>{
	public:
#ifdef DEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif
		VulkanInstance();
		~VulkanInstance();

		// Not copyable or movable
		VulkanInstance(const VulkanInstance&);
		void operator=(const VulkanInstance&);
		VulkanInstance(VulkanInstance&&) = delete;
		VulkanInstance& operator=(VulkanInstance&&) = delete;

		VkInstance instance() { return _instance; }
		VkCommandPool getCommandPool() { return commandPool; }
		VkDevice device() { return _device; }
		VkPhysicalDevice physicalDevice() {return _physicalDevice; }
		VkSurfaceKHR surface() { return _surface; }
		VkQueue graphicsQueue() { return _graphicsQueue; }
		VkQueue presentQueue() { return _presentQueue; }

		SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(_physicalDevice); }
		QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(_physicalDevice); }
		VkFormat findSupportedFormat(
			const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		// Buffer Helper Functions


		VkPhysicalDeviceProperties properties;

	private:


		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createCommandPool();
		int deviceScore(VkPhysicalDevice device);
		// helper functions
		bool isDeviceSuitable(VkPhysicalDevice device);
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void hasGflwRequiredInstanceExtensions();
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
		VkCommandPool commandPool;
		VkInstance _instance;
		VkDevice _device;
		VkSurfaceKHR _surface;
		VkQueue _graphicsQueue;
		VkQueue _presentQueue;

		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation", };
		const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	};

}
#endif //VULKANINSTANCE_H