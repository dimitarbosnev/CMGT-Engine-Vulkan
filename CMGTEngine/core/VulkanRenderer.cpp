#pragma once
#include "VulkanRenderer.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
namespace cmgt {
	void VulkanRenderer::InitializeRenderer() {
		assignInstance(new VulkanRenderer());
	}
	VulkanRenderer::VulkanRenderer() {

	}
	void VulkanRenderer::AddMeshToRender(Mesh& mesh) {
		getInstance().meshesToRender.push_back(&mesh);
	}
	Camera& VukanRenderer::getCamera()
	{
		return *SceneManager::getInstance().getCurrentScene().getWorld().getMainCamera();
	}
}
