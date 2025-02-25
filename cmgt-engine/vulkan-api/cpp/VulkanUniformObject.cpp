
#include "vulkan-api/VulkanUniformObject.h"
#include "vulkan-api/VulkanSwapchain.h"
#include "vulkan-api/VulkanImage.h"
#include "minimal/Log.h"
#include <cassert>
#include <stdexcept>

namespace cmgt {

	bool getDescriptorUsage(const VkDescriptorType& type){
		bool withBuffer;
		switch (type)
		{
		case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
		case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
		case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
		case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
		case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
		case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
			{
				withBuffer = true;
			}
			break;
		
		case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
		case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
		case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
		case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
			{
				withBuffer = false;
			}
			break;
		}

		return withBuffer;
	}

	// *************** Vulkan Uniform Object Builder *********************

	VulkanUniformObject::Builder& VulkanUniformObject::Builder::addBinding(uint32_t binding, VkDescriptorType descriptorType, 
		VkShaderStageFlags stageFlags, size_t size){
		
		assert(bindings.count(binding) == 0 && "Binding already in use");

		VkDescriptorSetLayoutBinding layoutBinding{};
		layoutBinding.binding = binding;
		layoutBinding.descriptorType = descriptorType;
		layoutBinding.descriptorCount = 1;
		layoutBinding.stageFlags = stageFlags;
		bindings[binding].layout = layoutBinding;
		bindings[binding].size = size;
		//save the size of the descriptor to somewhere

		return *this;
	}

	// *************** Vulkan Uniform Object *********************

	VulkanUniformObject::VulkanUniformObject(VulkanUniformObject::Builder& builder, VulkanInstance* pInstance) : bindings(builder.bindings), instance(pInstance){
		//resize DescriptorSet array
		descriptors.resize(builder.descriptorCount);

		//creating VkDescriptorSetLayout
		std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings{};
		for (auto& kv : bindings) {
			setLayoutBindings.push_back(kv.second.layout);
		}
		
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.bindingCount = setLayoutBindings.size();
		descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

		if (vkCreateDescriptorSetLayout(instance->device(), &descriptorSetLayoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error(Log::error_critical("failed to create descriptor set layout!"));
		}
		
		//creating VkDescriptorPool
		std::vector<VkDescriptorPoolSize> poolSizes{};
		for (auto& binding : bindings) {
			VkDescriptorPoolSize poolSize{};
			poolSize.descriptorCount = descriptors.size();
			poolSize.type = binding.second.layout.descriptorType;
			poolSizes.push_back(poolSize);
		}

			VkDescriptorPoolCreateInfo descriptorPoolInfo{};
			descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			descriptorPoolInfo.poolSizeCount = poolSizes.size();
			descriptorPoolInfo.pPoolSizes = poolSizes.data();
			descriptorPoolInfo.maxSets = descriptors.size();
			descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT; // set it up later

		if (vkCreateDescriptorPool(instance->device(), &descriptorPoolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
			throw std::runtime_error(Log::error_critical("failed to create descriptor pool!"));
		}

		//create Buffers
		for (auto& binding : bindings) {
			// TODO: create a sampler depending on descriptor type
			if(getDescriptorUsage(binding.second.layout.descriptorType)){
				VulkanBuffer* buffer = new VulkanBuffer(instance->physicalDevice(), instance->device(),binding.second.size, descriptors.size(),
				getBufferUsage(binding.second.layout), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
				buffer->map();
				binding.second.buffer = buffer;
				binding.second.bufferInfo = buffer->descriptorInfo();
				writeBuffer(binding.first);
			} else {
				//VulkanImage* image = new VulkanImage(instance->physicalDevice(), instance->device())
				//And here I decided to pivot towards openGL glhf
			}


		}


		//create DescriptorSets
		for(VkDescriptorSet& set : descriptors){
			createDescriptor(set);
			updateDescriptor(set);
		}
		
	}

	VulkanUniformObject::~VulkanUniformObject(){
		freeDescriptors();
		for (auto& binding : bindings){
			delete binding.second.buffer;
		}
		bindings.clear();
		vkDestroyDescriptorPool(instance->device(), descriptorPool, nullptr);
		vkDestroyDescriptorSetLayout(instance->device(), descriptorSetLayout, nullptr);
	}

	void VulkanUniformObject::writeImage(uint32_t index){
		assert(bindings.count(index) == 1 && "Layout does not contain specified binding");

		auto& binding = bindings[index];

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = binding.layout.descriptorType;
		write.dstBinding = index;
		write.pImageInfo = &binding.imageInfo;
		write.descriptorCount = 1;

		binding.descriptorWrite = write;
	}

	void VulkanUniformObject::writeBuffer(uint32_t index){
		assert(bindings.count(index) == 1 && "Layout does not contain specified binding");

		auto& binding = bindings[index];

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = binding.layout.descriptorType;
		write.dstBinding = index;
		write.pBufferInfo = &binding.bufferInfo;
		write.descriptorCount = 1;

		binding.descriptorWrite = write;
	}

	void VulkanUniformObject::createDescriptor(VkDescriptorSet& descriptor){
		// Might want to create a "DescriptorPoolManager" class that handles this case, and builds
		// a new pool whenever an old pool fills up. But this is beyond our current scope
		
		VkDescriptorSetLayout layout = descriptorSetLayout;
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = descriptorPool;
		allocInfo.pSetLayouts = &layout;
		allocInfo.descriptorSetCount = 1;
		if (vkAllocateDescriptorSets(instance->device(), &allocInfo, &descriptor) != VK_SUCCESS) {
			throw std::runtime_error(Log::error_critical("failed to allocate descriptor sets!"));
		}
	}

	void VulkanUniformObject::updateDescriptor(VkDescriptorSet& descriptor){
		std::vector<VkWriteDescriptorSet> writes{};
		for (auto& kv : bindings) {
			VkWriteDescriptorSet write = kv.second.descriptorWrite;
			write.dstSet = descriptor;
			writes.push_back(write);
		}
		vkUpdateDescriptorSets(instance->device(), writes.size(), writes.data(), 0, nullptr);
	}

	void VulkanUniformObject::updateBufferSize(uint32_t index, size_t size){
		assert(bindings.count(index) == 1 && "Layout does not contain specified binding");

		auto& binding = bindings[index];

		binding.buffer->resizeBuffer(size);

		for(VkDescriptorSet& set : descriptors){
			VkWriteDescriptorSet write = binding.descriptorWrite;
			write.dstSet = set;
			vkUpdateDescriptorSets(instance->device(), 1, &binding.descriptorWrite, 0, nullptr);
		}
	}

	void VulkanUniformObject::freeDescriptors(){
		vkFreeDescriptorSets(instance->device(), descriptorPool, descriptors.size(), descriptors.data());
	}
	void VulkanUniformObject::resetPool(){
		vkResetDescriptorPool(instance->device(), descriptorPool, 0);
	}

}  // namespace cmgt