#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once
#include <string>
#include<map>
#include "minimal/types.h"

namespace cmgt
{
    class Object;
    class ObjectManager : public Singelton<ObjectManager> {
    public:
        ObjectManager();
        ~ObjectManager();
        void addObject(Object* obj);
        Object* getObject(std::string name);
        Object* getObject(id_t pID);
        id_t assignObjectID();
        void deleteObject(Object* obj);
        void deleteObject(id_t pID);

    private:
        std::map<id_t, Object*> Objects{};
        ObjectManager(const ObjectManager&) = delete;
        ObjectManager operator=(const ObjectManager&) = delete;
    };
}
#endif // OBJECTMANAGER_H