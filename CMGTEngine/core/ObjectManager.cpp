#pragma once
#include "ObjectManager.hpp"
#include "GameObject.hpp"
namespace cmgt {

	void ObjectManager::InitializesObjectManager() {
		assignInstance(new ObjectManager());
	}

	ObjectManager::~ObjectManager()
	{
		for (auto& obj : gameObjects) {
			delete obj.second;
		}
		gameObjects.clear();
	}
	void ObjectManager::addGameObject(GameObject& obj) {
		getInstance().gameObjects.emplace(obj.getID(), &obj);
	}
	GameObject& ObjectManager::getGameObject(string name)
	{
		ObjectManager& manager = getInstance();
		auto findByName = [name](const pair<id_t, GameObject*>& a) { return a.second->getName() == name; };
		auto it = find_if(manager.gameObjects.begin(), manager.gameObjects.end(), findByName);
		return *it->second;
	}
	GameObject& ObjectManager::getGameObject(id_t pID)
	{
		return *getInstance().gameObjects.find(pID)->second;
	}
	id_t ObjectManager::assignGameObjectID()
	{
		ObjectManager& objectManager = getInstance();
		id_t i = 0;
		while (objectManager.gameObjects.contains(i)) {
			i++;
		}
		return i;
	}
	void ObjectManager::deleteGameObject(GameObject& obj) { deleteGameObject(obj.getID()); }
	void ObjectManager::deleteGameObject(id_t pID) { 
		ObjectManager& manager = getInstance();
		delete& manager.gameObjects[pID];
		manager.gameObjects.erase(pID);
	}
}