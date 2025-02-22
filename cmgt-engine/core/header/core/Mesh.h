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
			std::vector<uint32_t> indices;

			void loadModel(const std::string& filePath);
		};
		Mesh(const std::string& fileName, Material* pMaterial);
		Mesh(const std::vector<Vertex>& vertecies, Material* pMaterial);
		virtual ~Mesh();
		void render(const VulkanFrameData& frameData) override;
		void update(float dt) override;
		void setVertexData(const std::vector<Vertex>& vertecies) {vertexData = vertecies;}
		const std::vector<Vertex>& getVertexData() { return vertexData;}
	protected:
		Material* _material;
		VulkanBuffer* vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer = false;
		VulkanBuffer* indexBuffer;
		uint32_t indexCount;
		void createVertexBuffers(const std::vector<Vertex>& vertecies);
		void createIndexBuffers(const std::vector<uint32_t>& indices);

	private:
		std::vector<Vertex> vertexData;
		Mesh(const Mesh&);
		Mesh& operator=(const Mesh&);
	};
}
#endif // MESH_H
