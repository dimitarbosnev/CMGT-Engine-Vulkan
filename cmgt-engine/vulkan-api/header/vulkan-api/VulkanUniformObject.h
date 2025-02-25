#ifndef VULKANUNIFORMOBJECT_H
#define VULKANUNIFORMOBJECT_H
#pragma once

#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/VulkanBuffer.h"
#include "vulkan-api/VulkanSwapchain.h"
// std
#include <unordered_map>
#include <vector>
#include <tuple>
namespace cmgt {

	bool getDescriptorUsage(const VkDescriptorType& type);

	class VulkanUniformObject{
	public:

	struct VulkanDescriptorBinding{
		size_t size = 0;
		VkDescriptorSetLayoutBinding layout;
		VkWriteDescriptorSet descriptorWrite;
		VulkanBuffer* buffer = nullptr;
		VkDescriptorBufferInfo bufferInfo;
		
		// add vulkan sampler in the future
		
		VkDescriptorImageInfo  imageInfo;
	};

	class Builder {
		friend class VulkanUniformObject;
		public:
		Builder& setDescriptorCount(uint32_t count) { descriptorCount = count; }
			Builder& addBinding(
				uint32_t binding,
				VkDescriptorType descriptorType,
				VkShaderStageFlags stageFlags, 
				size_t size);
		private:
		std::unordered_map<uint32_t, VulkanDescriptorBinding> bindings{};
		uint32_t descriptorCount = MAX_FRAMES_IN_FLIGHT;
	};

	public:

		VulkanUniformObject(Builder& builder, VulkanInstance* pInstance);
		~VulkanUniformObject();

		VkDescriptorSetLayout getLayout() { return descriptorSetLayout; }
		void updateBufferSize(uint32_t index, size_t size);
		void freeDescriptors();
		void resetPool();
	private:
		void writeImage(uint32_t index);
		void writeBuffer(uint32_t index);

		void createDescriptor(VkDescriptorSet& descriptor);
		void updateDescriptor(VkDescriptorSet& descriptor);

		VulkanInstance* instance;
		VkDescriptorSetLayout descriptorSetLayout;
		std::unordered_map<uint32_t,VulkanDescriptorBinding> bindings;
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptors{};

	public:
		uint32_t bindingsSize() { return bindings.size(); }

		VulkanBuffer* getBufferAt(uint32_t index){
			return bindings[index].buffer;
		}

		VkDescriptorSet& getDescriptorSet(uint32_t index){
			return descriptors[index];
		}
	};
	
}  // namespace cmgt


#endif //VULKANUNIFORMOBJECT_H