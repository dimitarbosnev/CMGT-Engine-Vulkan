#ifndef VULKANIMAGE_H
#define VULKANIMAGE_H
#pragma once
#include <vulkan/vulkan.h>

namespace cmgt {

    VkImageUsageFlags getImageUsage(const VkDescriptorSetLayoutBinding& binding);

    class VulkanImage {
        public:
            VulkanImage(
                VkPhysicalDevice physicalDevice,
                VkDevice device,
                uint32_t width,
                uint32_t height,
                uint32_t layers,
                VkFormat format,
                VkImageUsageFlags usageFlags,
                VkMemoryPropertyFlags memoryPropertyFlags,
                VkImageLayout layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
            );
            ~VulkanImage();
    
            VulkanImage(const VulkanImage&) = delete;
            VulkanImage& operator=(const VulkanImage&) = delete;
    
            VkImage getImage() const { return image; }
            VkImageView getImageView() const { return imageView; }
            VkDeviceMemory getMemory() const { return memory; }

            void writeToImage(const void* data, VkDeviceSize pixelSize, uint32_t pixelCount, VkQueue queue, VkCommandPool commandPool);
            void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout newLayout, VkCommandPool commandPool, VkQueue queue);
            VkDescriptorImageInfo descriptorInfo();
        private:
            void createImage(VkImageUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags);
            VkDevice vkDevice;
            VkPhysicalDevice vkPhysicalDevice;
            VkImage image = VK_NULL_HANDLE;
            VkDeviceMemory memory = VK_NULL_HANDLE;
            VkImageView imageView = VK_NULL_HANDLE;
            VkSampler imageSampler = VK_NULL_HANDLE;
            uint32_t width, height, layerCount;
            VkFormat format;
            VkImageLayout currentLayout;
        };

}  // namespace cmgt
#endif //VULKANIMAGE_H