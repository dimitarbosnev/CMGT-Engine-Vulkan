#ifndef VULKANFRAMEDATA_H
#define VULKANFRAMEDATA_H
#pragma once
#include "vulkan-api/VulkanInstance.h"
#include "minimal/glm.h"
namespace cmgt {
    struct VulkanFrameData {
	public:
		VulkanFrameData(const VkCommandBuffer& pCommandBuffer, const short& pImageIndex, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
			: commandBuffer(pCommandBuffer), imageIndex(pImageIndex), viewMatrix(pViewMatrix), projectionMatrix(pProjectionMatrix) {}
		const VkCommandBuffer& commandBuffer;
		const short& imageIndex;
		const glm::mat4& viewMatrix;
		const glm::mat4& projectionMatrix;

	};
}
#endif //VULKANFRAMEDATA_H