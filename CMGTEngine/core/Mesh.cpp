#pragma once
#include <iostream>
#include <string>
#include "Mesh.hpp"
#include "VulkanInstance.hpp"
#include "VulkanRenderer.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
namespace cmgt {
	Mesh::Mesh(const Mesh::Builder &builder) {
		createVertexBuffers(builder.vertecies);
		createIndexBuffers(builder.indices);
		VulkanRenderer::AddMeshToRender(*this);
	}

	Mesh::~Mesh() {
		VkDevice device = VulkanInstance::getInstance().device();
		vkDestroyBuffer(device, _vertexBuffer, nullptr);
		vkFreeMemory(device, _vertexBufferMemory, nullptr);

		if (hasIndexBuffer) {
			vkDestroyBuffer(device, _indexBuffer, nullptr);
			vkFreeMemory(device, _indexBufferMemory, nullptr);
		}
	}

	void Mesh::createVertexBuffers(const vector<Vertex>& vertecies){
		VulkanInstance& instance = VulkanInstance::getInstance();
		vertexCount = static_cast<uint32_t>(vertecies.size());
		assert(vertexCount >= 3 && "Vertex count must be atleast 3!");
		VkDeviceSize bufferSize = sizeof(Vertex) * vertexCount;
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		instance.createBuffer(bufferSize, 
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer, stagingBufferMemory);



		void* data;
		vkMapMemory(instance.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data,vertecies.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(instance.device(), stagingBufferMemory);

		instance.createBuffer(bufferSize,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			_vertexBuffer, _vertexBufferMemory);
		instance.copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

		vkDestroyBuffer(instance.device(), stagingBuffer, nullptr);
		vkFreeMemory(instance.device(), stagingBufferMemory, nullptr);
	}
	void Mesh::createIndexBuffers(const vector<uint32_t>& indices)
	{
		VulkanInstance& instance = VulkanInstance::getInstance();
		indexCount = static_cast<uint32_t>(indices.size());
		hasIndexBuffer = indexCount > 0;
		if (!hasIndexBuffer) return;
		VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		instance.createBuffer(bufferSize,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(instance.device(), _indexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(instance.device(), _indexBufferMemory);

		instance.createBuffer(bufferSize,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT , VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			_indexBuffer, _indexBufferMemory);

		instance.copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

		vkDestroyBuffer(instance.device(), stagingBuffer, nullptr);
		vkFreeMemory(instance.device(), stagingBufferMemory, nullptr);
	}
	void Mesh::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = { _vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers,offsets);

		if (hasIndexBuffer) vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void Mesh::render(VkCommandBuffer commandBuffer) {
		if (hasIndexBuffer) vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
		else vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
	}
	void Mesh::update(float dt) {

	}
	Mesh* Mesh::createModelFromFile(const string& fileName)
	{
		string filePath = paths::CMGT_MODEL_PATH + fileName;
		Builder builder;
		builder.loadModel(filePath);

		return new Mesh(builder);
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
		vector<VkVertexInputAttributeDescription> attributeDescriptions(3);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex,normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, uv);
		return attributeDescriptions;
	}

	void Mesh::Builder::loadModel(const string& filePath) {
		tinyobj::attrib_t attrib;
		vector<tinyobj::shape_t> shapes;
		vector<tinyobj::material_t> materials;
		string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
			throw runtime_error(warn + err);
		}
		vertecies.clear();
		indices.clear();

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex;

				if (index.vertex_index >= 0) {
					vertex.position = { attrib.vertices[3 * index.vertex_index + 0],
										attrib.vertices[3 * index.vertex_index + 1],
										attrib.vertices[3 * index.vertex_index + 2] };
				}

				if (index.normal_index >= 0) {
					vertex.normal = { attrib.normals[3 * index.normal_index + 0],
									  attrib.normals[3 * index.normal_index + 1],
									  attrib.normals[3 * index.normal_index + 2] };
				}

				if (index.texcoord_index >= 0) {
					vertex.uv = { attrib.texcoords[2 * index.texcoord_index + 0],
								  attrib.texcoords[2 * index.texcoord_index + 1]};
				}

				vertecies.push_back(vertex);
			}

		}
	}
}


