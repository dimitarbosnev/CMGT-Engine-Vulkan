
#include "core/ObjectManager.h"
#include "core/GameObject.h"
namespace cmgt {


	ObjectManager::ObjectManager() : Singelton<ObjectManager>(this){
		
	}
	ObjectManager::~ObjectManager()
	{
		for (auto& obj : Objects) {
			delete obj.second;
		}
		Objects.clear();
	}
	void ObjectManager::addObject(Object* obj) {
		id_t newID = assignObjectID();
		obj->_id = newID;
		Objects.emplace(newID, obj);
	}
	Object* ObjectManager::getObject(std::string name)
	{
		auto findByName = [name](const std::pair<id_t, Object*>& a) { return a.second->_name == name; };
		auto it = find_if(Objects.begin(), Objects.end(), findByName);
		return it->second;
	}
	Object* ObjectManager::getObject(id_t pID)
	{
		return Objects.find(pID)->second;
	}
	id_t ObjectManager::assignObjectID()
	{
		id_t i = 0;
		while (Objects.contains(i)) {
			i++;
		}
		return i;
	}
	void ObjectManager::deleteObject(Object* obj) { deleteObject(obj->_id); }
	void ObjectManager::deleteObject(id_t pID) { 
		delete Objects[pID];
		Objects.erase(pID);
	}
}