
#include "core/Scene.h"
#include "core/SceneManager.h"
#include "core/config.h"
namespace cmgt{

	Scene::Scene(string pName) : name{ pName }, id{ SceneManager::assignSceneID() } {
		SceneManager::addScene(*this);
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