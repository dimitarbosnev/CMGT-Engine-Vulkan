#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once
#include "core/config.h"
#include <string>
#include<map>

using namespace std;

namespace cmgt
{
    class GameObject;
    class ObjectManager : public Singleton<ObjectManager> {
    public:
        static void InitializesObjectManager();
        ~ObjectManager();
        static void addGameObject(GameObject& obj);
        static GameObject& getGameObject(string name);
        static GameObject& getGameObject(id_t pID);
        static id_t assignGameObjectID();
        static void deleteGameObject(GameObject& obj);
        static void deleteGameObject(id_t pID);

    private:
        map<id_t, GameObject*> gameObjects;
        ObjectManager() = default;
        ObjectManager(const ObjectManager&) = delete;
        ObjectManager operator=(const ObjectManager&) = delete;
    };
}
#endif // OBJECTMANAGER_H