
#include "vulkan-api/VulkanImage.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanBuffer.h"
#include <cassert>
#include <cstring>
#include <exception>
namespace cmgt {

    VkImageUsageFlags getImageUsage(const VkDescriptorSetLayoutBinding& binding){

		VkImageUsageFlags flag{};
		
		switch (binding.descriptorType)
		{
		case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
		case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
		{
			flag = VK_IMAGE_USAGE_SAMPLED_BIT;
			break;
		}		
		case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
		{
			flag = VK_IMAGE_USAGE_STORAGE_BIT;
			break;
		}
		case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
		{
			flag = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
			break;
		}
		}
		return flag;
	}

    VulkanImage::VulkanImage(
        VkPhysicalDevice physicalDevice,
        VkDevice device,
        uint32_t width,
        uint32_t height,
        uint32_t layers,
        VkFormat format,
        VkImageUsageFlags usageFlags,
        VkMemoryPropertyFlags memoryPropertyFlags,
        VkImageLayout layout)
        : vkPhysicalDevice(physicalDevice), vkDevice(device), width(width), height(height), layerCount(layers), format(format), currentLayout(layout) {
        
        createImage(usageFlags, memoryPropertyFlags);
    }

    VulkanImage::~VulkanImage() {
        vkDestroyImageView(vkDevice, imageView, nullptr);
        vkDestroyImage(vkDevice, image, nullptr);
        vkFreeMemory(vkDevice, memory, nullptr);
    }

    void VulkanImage::createImage(VkImageUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = layerCount;
        imageInfo.format = format;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = currentLayout; // might cause a problem
        imageInfo.usage = usageFlags;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        createImageWithInfo(imageInfo, memoryPropertyFlags, image, memory, vkPhysicalDevice, vkDevice);

        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = layerCount;

        if (vkCreateImageView(vkDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image view!");
        }

    }

    void VulkanImage::writeToImage(const void* data, VkDeviceSize pixelSize, uint32_t pixelCount, VkQueue queue, VkCommandPool commandPool){

        // Create a staging buffer that is host-visible.
        VulkanBuffer stagingBuffer(vkPhysicalDevice, vkDevice, pixelSize * pixelCount, layerCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        // Map the staging buffer and copy pixel data.
        stagingBuffer.map();
		stagingBuffer.writeToBuffer(data);
        
        // Copy the staging buffer into the image.
        copyBufferToImage(stagingBuffer.getBuffer(), image, width,height, layerCount, vkDevice, queue, commandPool);
         
        transitionImageLayout(image, format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, commandPool, queue);
    }

    void VulkanImage::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout newLayout, VkCommandPool commandPool, VkQueue queue) 
    { VkCommandBuffer commandBuffer = beginSingleTimeCommands(vkDevice, commandPool);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = currentLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = layerCount;
        
        // For a color image we only need the color aspect.
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        
        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;
        
        if (currentLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
             barrier.srcAccessMask = 0;
             barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
             sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
             destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if (currentLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
             barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
             barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
             sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
             destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        } else {
             throw std::invalid_argument("unsupported layout transition!");
        }
        
        vkCmdPipelineBarrier(
             commandBuffer,
             sourceStage, destinationStage,
             0,
             0, nullptr,
             0, nullptr,
             1, &barrier
        );
        
        endSingleTimeCommands(commandBuffer, vkDevice, queue, commandPool);
        
    }

    VkDescriptorImageInfo VulkanImage::descriptorInfo(){
        VkDescriptorImageInfo info;
        info.imageLayout = currentLayout;
        info.imageView = imageView;
        info.sampler = imageSampler;
    }
}  // namespace cmgt