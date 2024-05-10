#ifndef VULKANSWAPCHIAN_HPP
#define VULKANSWAPCHIAN_HPP

#pragma once
#include "VulkanInstance.hpp"
#include "config.hpp"
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
namespace cmgt {

	class VulkanSwapchain : public Singleton<VulkanSwapchain>{
	public:
		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

		static void InitializeSwapchain(VkExtent2D windowExtent);
		static void RecreateSwapchain(VkExtent2D windowExtent);
		~VulkanSwapchain();

		VulkanSwapchain(const VulkanSwapchain&) = delete;
		void operator=(const VulkanSwapchain&) = delete;

		VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
		VkRenderPass getRenderPass() { return renderPass; }
		VkImageView getImageView(int index) { return swapChainImageViews[index]; }
		size_t imageCount() { return swapChainImages.size(); }
		VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
		VkExtent2D getSwapChainExtent() { return swapChainExtent; }
		uint32_t width() { return swapChainExtent.width; }
		uint32_t height() { return swapChainExtent.height; }

		float extentAspectRatio() {
			return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
		}
		VkFormat findDepthFormat();

		VkResult acquireNextImage(uint32_t* imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

	private:
		VulkanSwapchain(VkExtent2D extent);
		VulkanSwapchain(VkExtent2D extent,VulkanSwapchain* pSwapchain);

		void initSwapchain();
		void createSwapChain();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		// Helper functions
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(
			const vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(
			const vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		VulkanSwapchain* previousSwapchain = nullptr;

		vector<VkFramebuffer> swapChainFramebuffers;
		VkRenderPass renderPass;

		vector<VkImage> depthImages;
		vector<VkDeviceMemory> depthImageMemorys;
		vector<VkImageView> depthImageViews;
		vector<VkImage> swapChainImages;
		vector<VkImageView> swapChainImageViews;

		VkExtent2D windowExtent;
		VkSwapchainKHR swapChain;

		vector<VkSemaphore> imageAvailableSemaphores;
		vector<VkSemaphore> renderFinishedSemaphores;
		vector<VkFence> inFlightFences;
		vector<VkFence> imagesInFlight;
		size_t currentFrame = 0;
	};

}

#endif //VULKANSWAPCHIAN_HPP
