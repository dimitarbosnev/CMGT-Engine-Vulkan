#ifndef MESH_H
#define MESH_H

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "core/Component.h"
#include "vulkan-api/VulkanBuffer.h"
#include "core/VulkanRenderer.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include "core/Material.h"

namespace cmgt {
	class Mesh : public Component
	{
	public:
		struct Builder {
		public:
			std::vector<Vertex> vertecies;
			vector<uint32_t> indices;

			void loadModel(const string& filePath);
		};
		virtual ~Mesh();
		void render(const VulkanFrameData& frameData);
		void update(float dt) override;
		Mesh(const vector<Vertex>&, Material* pMaterial);
		static Mesh* createModelFromFile(const string& filePath, Material* pMaterial);
	protected:
		VulkanInstance& instnace;
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
