#ifndef TYPES_H
#define TYPES_H

#define EPSILON std::numeric_limits<float>::epsilon()
#define MAX std::numeric_limits<float>::max()
#define PHYSICS_STEP 60.f
#define TARGET_FPS 144
//can be moved to settings

#pragma once
#include "minimal/glm.h"
#include <chrono>
#include <vulkan/vulkan.h>
namespace cmgt {
    typedef long int id_t;
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::microseconds mc;
    typedef std::chrono::nanoseconds ns;

    struct Vertex {
	public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	inline static std::vector<VkVertexInputAttributeDescription> getAttributeDescription() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);
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
	inline static std::vector<VkVertexInputBindingDescription> getBindingDescription() {
		std::vector<VkVertexInputBindingDescription> bindingDescription(1);
		bindingDescription[0].binding = 0;
		bindingDescription[0].stride = sizeof(Vertex);
		bindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}
	};

	template<typename T>
	class Singelton{
	public:
		Singelton(T* instance){
			if(!_instance){
				_instance = instance;
			}
		}
		~Singelton() = default;
		inline static T* get(){
			assert(_instance && "No Instance created");
			return _instance;
		}
	private:
		inline static T* _instance = nullptr;
	};
}
#endif //TYPES_H