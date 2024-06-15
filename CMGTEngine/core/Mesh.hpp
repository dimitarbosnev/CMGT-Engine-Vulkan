#ifndef MESH_HPP
#define MESH_HPP

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "Component.hpp"
#include "glm.hpp"

using namespace glm;
using namespace std;

namespace cmgt {

	class Mesh : public Component
	{
	public:
		struct Vertex {
		public:
			vec3 position;
			vec3 normal;
			vec2 uv;

			static vector<VkVertexInputBindingDescription> getBindingDescription();
			static vector<VkVertexInputAttributeDescription> getAttributeDescription();
		};

		struct Builder {
		public:
			vector<Vertex> vertecies;
			vector<uint32_t> indices;

			void loadModel(const string& filePath);
		};
		Mesh(const Mesh::Builder &builder);
		virtual ~Mesh();
		void bind(VkCommandBuffer commandBuffer);
		void render(VkCommandBuffer commandBuffer);
		void update(float dt) override;

		static Mesh* createModelFromFile(const string& filePath);
	protected:

		VkBuffer _vertexBuffer;
		VkDeviceMemory _vertexBufferMemory;
		uint32_t vertexCount;

		bool hasIndexBuffer;
		VkBuffer _indexBuffer;
		VkDeviceMemory _indexBufferMemory;
		uint32_t indexCount;
		void createVertexBuffers(const vector<Vertex>& vertecies);
		void createIndexBuffers(const vector<uint32_t>& indices);

	private:
		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;
	};
}
#endif // MESH_HPP
