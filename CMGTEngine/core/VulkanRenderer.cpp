#pragma once
#include "VulkanRenderer.hpp"
namespace cmgt {
	void VulkanRenderer::InitializeRenderer() {
		assignInstance(new VulkanRenderer());
	}
	VulkanRenderer::VulkanRenderer() {

	}
	void VulkanRenderer::AddMeshToRender(Mesh& mesh) {
		getInstance().meshesToRender.push_back(&mesh);
	}
}
