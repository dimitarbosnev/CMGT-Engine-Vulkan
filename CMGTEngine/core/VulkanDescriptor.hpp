#ifndef VULKANDESCRIPTOR_HPP
#define VULKANDESCRIPTOR_HPP
#pragma once

#include "VulkanInstance.hpp"

// std
#include <unordered_map>
#include <vector>

namespace cmgt {

	class VulkanDescriptorSetLayout {
	public:
		class Builder {
		public:
			Builder& addBinding(
				uint32_t binding,
				VkDescriptorType descriptorType,
				VkShaderStageFlags stageFlags,
				uint32_t count = 1);
			VulkanDescriptorSetLayout build() const;

		private:
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
		};

		VulkanDescriptorSetLayout(std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
		~VulkanDescriptorSetLayout();

		VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

	private:
		VkDescriptorSetLayout descriptorSetLayout;
		std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

		friend class VulkanDescriptorWriter;
		VulkanDescriptorSetLayout(const VulkanDescriptorSetLayout&);
		VulkanDescriptorSetLayout& operator=(const VulkanDescriptorSetLayout&);
	};

	class VulkanDescriptorPool {
	public:
		class Builder {
		public:

			Builder& addPoolSize(VkDescriptorType descriptorType, uint32_t count);
			Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
			Builder& setMaxSets(uint32_t count);
			VulkanDescriptorPool build() const;

		private:
			std::vector<VkDescriptorPoolSize> poolSizes{};
			uint32_t maxSets = 1000;
			VkDescriptorPoolCreateFlags poolFlags = 0;
		};

		VulkanDescriptorPool(uint32_t maxSets,
			VkDescriptorPoolCreateFlags poolFlags,
			const std::vector<VkDescriptorPoolSize>& poolSizes);
		~VulkanDescriptorPool();
		VulkanDescriptorPool(const VulkanDescriptorPool&);
		bool allocateDescriptor(
			const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const;

		void freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;

		void resetPool();

	private:
		VkDescriptorPool descriptorPool;

		friend class VulkanDescriptorWriter;
		VulkanDescriptorPool& operator=(const VulkanDescriptorPool&);
	};

	class VulkanDescriptorWriter {
	public:
		VulkanDescriptorWriter(VulkanDescriptorSetLayout& pSetLayout, VulkanDescriptorPool& pool);
		~VulkanDescriptorWriter();
		VulkanDescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);
		VulkanDescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageInfo);

		bool build(VkDescriptorSet& set);
		void overwrite(VkDescriptorSet& set);

	private:
		VulkanDescriptorSetLayout& setLayout;
		VulkanDescriptorPool& pool;
		std::vector<VkWriteDescriptorSet> writes;
	};


}  // namespace cmgt


#endif //VULKANDESCRIPTOR_HPP