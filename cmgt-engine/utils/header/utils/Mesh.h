#ifndef MESH_H
#define MESH_H

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "core/Component.h"
#include "render-engine/VulkanBuffer.h"
#include "render-engine/VulkanRenderer.h"
#include "core/glm.h"
#include "core/Material.h"
#include "utils/TestMaterial.h"
using namespace std;

namespace cmgt {
	class Mesh : public Component
	{
	public:
		struct Vertex {
		public:
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;

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
		void render(const VulkanFrameData& frameData);
		void update(float dt) override;
		Mesh(const vector<Vertex>&, Material* pMaterial = new TestMaterial());
		static Mesh* createModelFromFile(const string& filePath, Material* pMaterial = new TestMaterial());
	protected:
		Material* _material;
		VulkanBuffer* vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer;
		VulkanBuffer* indexBuffer;
		uint32_t indexCount;
		void createVertexBuffers(const vector<Vertex>& vertecies);
		void createIndexBuffers(const vector<uint32_t>& indices);

	private:
		Mesh(const Mesh::Builder &builder, Material* pMaterial);
		Mesh(const Mesh&);
		Mesh& operator=(const Mesh&);
	};
}
#endif // MESH_H
