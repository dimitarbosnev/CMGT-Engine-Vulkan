#ifndef MESH_HPP
#define MESH_HPP

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "Component.hpp"
#include "../glm.hpp"

using namespace glm;
using namespace std;

namespace cmgt {
	class WorldSeed;

	/**
	 * A mesh represents an .OBJ file. It knows how it is constructed, how its data should be buffered to OpenGL
	 * and how it should be streamed to OpenGL
	 */
	class Mesh : public Component
	{
	public:
		struct Vertex {
		public:
			vec3 position;
			static vector<VkVertexInputBindingDescription> getBindingDescription();
			static vector<VkVertexInputAttributeDescription> getAttributeDescription();
		};
		Mesh();
		virtual ~Mesh();
		void bind(VkCommandBuffer commandBuffer);
		void render(VkCommandBuffer commandBuffer);
	protected:

		VkBuffer _vertexBuffer;
		VkDeviceMemory _vertexBufferMemory;
		void createVertexBuffers(const vector<Vertex>& vertecies);

	private:
		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;
	};
}
#endif // MESH_HPP
