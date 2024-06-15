#pragma once
#include "VulkanRenderer.hpp"
namespace cmgt {
	void VukanRenderer::InitializeRenderer() {
		assignInstance(new VukanRenderer());
	}
	VukanRenderer::VukanRenderer() {

	}
	void VukanRenderer::AddMeshToRender(Mesh& mesh) {
		getInstance().meshesToRender.push_back(&mesh);
	}
}
