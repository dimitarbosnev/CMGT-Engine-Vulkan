
#include "core/Scene.h"
#include "core/SceneManager.h"
namespace cmgt{

	Scene::Scene(std::string pName) {
	}

	Scene::~Scene(){
	}
	void Scene::update(float dt)
	{
		_world->update(dt);
	}
	void Scene::renderScene(VkCommandBuffer commandBuffer){

	}
}