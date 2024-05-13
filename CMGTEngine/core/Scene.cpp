#pragma once
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "config.hpp"
namespace cmgt{

	Scene::Scene(string pName) : name{ pName }, id{ SceneManager::assignSceneID() } {
		SceneManager::addScene(*this);
	}

	Scene::~Scene(){
	}
	void Scene::update(float dt)
	{
		_world.update(dt);
	}
	void Scene::renderScene()
	{
	}
}