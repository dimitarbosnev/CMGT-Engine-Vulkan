
#include "core/ObjectManager.h"
#include "core/GameObject.h"
namespace cmgt {


	ObjectManager::ObjectManager(){
		
	}
	ObjectManager::~ObjectManager()
	{
		for (auto& obj : gameObjects) {
			delete obj.second;
		}
		gameObjects.clear();
	}
	void ObjectManager::addGameObject(GameObject& obj) {
		gameObjects.emplace(obj.getID(), &obj);
	}
	GameObject& ObjectManager::getGameObject(std::string name)
	{
		auto findByName = [name](const std::pair<id_t, GameObject*>& a) { return a.second->getName() == name; };
		auto it = find_if(gameObjects.begin(), gameObjects.end(), findByName);
		return *it->second;
	}
	GameObject& ObjectManager::getGameObject(id_t pID)
	{
		return *gameObjects.find(pID)->second;
	}
	id_t ObjectManager::assignGameObjectID()
	{
		id_t i = 0;
		while (gameObjects.contains(i)) {
			i++;
		}
		return i;
	}
	void ObjectManager::deleteGameObject(GameObject& obj) { deleteGameObject(obj.getID()); }
	void ObjectManager::deleteGameObject(id_t pID) { 
		delete& gameObjects[pID];
		gameObjects.erase(pID);
	}
}