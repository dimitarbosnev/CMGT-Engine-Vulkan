#pragma once
#include <iostream>
#include <string>
#include "Mesh.hpp"
#include "VulkanInstance.hpp"
namespace cmgt {
	Mesh::Mesh(const vector<Vertex>& vertecies) {
		createVertexBuffers(vertecies);
	}

	Mesh::~Mesh() {
		VkDevice device = VulkanInstance::getInstance().device();
		vkDestroyBuffer(device, _vertexBuffer, nullptr);
		vkFreeMemory(device, _vertexBufferMemory, nullptr);
	}

	void Mesh::createVertexBuffers(const vector<Vertex>& vertecies){
		VulkanInstance& instance = VulkanInstance::getInstance();
		vertexCount = static_cast<uint32_t>(vertecies.size());
		assert(vertexCount >= 3 && "Vertex count must be atleast 3!");
		VkDeviceSize bufferSize = sizeof(Vertex) * vertexCount;
		instance.createBuffer(bufferSize, 
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			_vertexBuffer,_vertexBufferMemory);

		void* data;
		vkMapMemory(instance.device(), _vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data,vertecies.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(instance.device(), _vertexBufferMemory);
	}
	void Mesh::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = { _vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers,offsets);
	}

	void Mesh::render(VkCommandBuffer commandBuffer) {
		vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
	}
	vector<VkVertexInputBindingDescription> Mesh::Vertex::getBindingDescription()
	{
		vector<VkVertexInputBindingDescription> bindingDescription(1);
		bindingDescription[0].binding = 0;
		bindingDescription[0].stride = sizeof(Vertex);
		bindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}
	vector<VkVertexInputAttributeDescription> Mesh::Vertex::getAttributeDescription()
	{
		vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex,color);
		return attributeDescriptions;
	}
}


