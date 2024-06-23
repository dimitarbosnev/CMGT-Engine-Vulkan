#ifndef MESH_HPP
#define MESH_HPP

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "Component.hpp"
#include "glm.hpp"
#include "Material.hpp"
#include "TestMaterial.hpp"
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
		virtual ~Mesh();
		void render(VkCommandBuffer commandBuffer, const mat4& pViewMatrix, const mat4& pPerspectiveMatrix);
		void update(float dt) override;
		Mesh(const vector<Vertex>&, Material* pMaterial = new TestMaterial());
		static Mesh* createModelFromFile(const string& filePath, Material* pMaterial = new TestMaterial());
	protected:
		Material* _material;
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
		Mesh(const Mesh::Builder &builder, Material* pMaterial);
		Mesh(const Mesh&);
		Mesh& operator=(const Mesh&);
	};
}
#endif // MESH_HPP
