#ifndef VULKANFRAMEDATA_H
#define VULKANFRAMEDATA_H
#pragma once
#include "vulkan-api/VulkanInstance.h"
#include "minimal/glm.h"
#include "minimal/types.h"
#include <array>
namespace cmgt {
    struct VulkanFrameData {
	public:
		VulkanFrameData(const VkCommandBuffer& pCommandBuffer, uint8_t pImageIndex, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, std::array<LightStruct,100>& pLights)
			: commandBuffer(pCommandBuffer), imageIndex(pImageIndex), viewMatrix(pViewMatrix), projectionMatrix(pProjectionMatrix), lights(pLights) {}
		const VkCommandBuffer& commandBuffer;
		uint8_t imageIndex;
		const glm::mat4& viewMatrix;
		const glm::mat4& projectionMatrix;
		std::array<LightStruct,100>& lights;
	};
}
#endif //VULKANFRAMEDATA_H