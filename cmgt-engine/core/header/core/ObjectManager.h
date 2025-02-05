#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once
#include <string>
#include<map>
#include "minimal/types.h"

namespace cmgt
{
    class GameObject;
    class ObjectManager : public Singelton<ObjectManager> {
    public:
        ObjectManager();
        ~ObjectManager();
        void addGameObject(GameObject& obj);
        GameObject& getGameObject(std::string name);
        GameObject& getGameObject(id_t pID);
        id_t assignGameObjectID();
        void deleteGameObject(GameObject& obj);
        void deleteGameObject(id_t pID);

    private:
        std::map<id_t, GameObject*> gameObjects;
        ObjectManager(const ObjectManager&) = delete;
        ObjectManager operator=(const ObjectManager&) = delete;
    };
}
#endif // OBJECTMANAGER_H