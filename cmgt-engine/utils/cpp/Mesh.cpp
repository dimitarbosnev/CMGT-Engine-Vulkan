
#include <iostream>
#include <string>
#include "utils/Mesh.h"
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanRenderer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
namespace cmgt {
	Mesh::Mesh(const Mesh::Builder &builder, Material* pMaterial) : _material(pMaterial){
		createVertexBuffers(builder.vertecies);
		createIndexBuffers(builder.indices);
	}

	Mesh::~Mesh() {
		VkDevice device = VulkanInstance::getInstance().device();
		delete _material;
		delete vertexBuffer;
		delete indexBuffer;
	}

	void Mesh::createVertexBuffers(const vector<Vertex>& vertecies){
		VulkanInstance& instance = VulkanInstance::getInstance();
		vertexCount = vertecies.size();
		assert(vertexCount >= 3 && "Mesh Vertex count must be atleast 3!");
		VulkanBuffer stagingBuffer(sizeof(Vertex), vertexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)vertecies.data());

		vertexBuffer = new VulkanBuffer(sizeof(Vertex), vertexCount, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		instance.copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), sizeof(Vertex)*vertexCount);
	}
	void Mesh::createIndexBuffers(const vector<uint32_t>& indices){
		VulkanInstance& instance = VulkanInstance::getInstance();
		indexCount = indices.size();
		hasIndexBuffer = indexCount > 0;
		if (!hasIndexBuffer) return;

		VulkanBuffer stagingBuffer(sizeof(uint32_t), indexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)indices.data());

		indexBuffer = new VulkanBuffer(sizeof(uint32_t), indexCount, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		instance.copyBuffer(stagingBuffer.getBuffer(), indexBuffer->getBuffer(), sizeof(uint32_t)*indexCount);
	}

	void Mesh::render(const VulkanFrameData& frameData) {

		VkBuffer buffers[] = { vertexBuffer->getBuffer() };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(frameData.commandBuffer, 0, 1, buffers, offsets);
		if (hasIndexBuffer) vkCmdBindIndexBuffer(frameData.commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);

		_material->bindPushConstants(frameData, getTransform());

		if (hasIndexBuffer) vkCmdDrawIndexed(frameData.commandBuffer, indexCount, 1, 0, 0, 0);
		else vkCmdDraw(frameData.commandBuffer, vertexCount, 1, 0, 0);
	}
	void Mesh::update(float dt) {
		_material->getPipeline()->AddMeshToRender(this);
	}
	Mesh::Mesh(const vector<Vertex>& vertecies, Material* pMaterial) : _material(pMaterial) {
		createVertexBuffers(vertecies);
	}
	Mesh* Mesh::createModelFromFile(const string& fileName, Material* pMaterial)
	{
		string filePath = CMGT_MODEL_PATH + fileName;
		Builder builder;
		builder.loadModel(filePath);

		return new Mesh(builder,pMaterial);
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


