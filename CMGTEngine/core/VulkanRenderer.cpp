#pragma once
#include "VulkanRenderer.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
namespace cmgt {
	void VukanRenderer::InitializeRenderer() {
		assignInstance(new VukanRenderer());
	}
	VukanRenderer::VukanRenderer() {

	}
	void VukanRenderer::AddMeshToRender(Mesh& mesh) {
		getInstance().meshesToRender.push_back(&mesh);
	}
	Camera& VukanRenderer::getCamera()
	{
		return *SceneManager::getInstance().getCurrentScene().getWorld().getMainCamera();
	}
}
