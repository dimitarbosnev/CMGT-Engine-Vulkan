#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "core/GameObject.h"
#include "core/World.h"

namespace cmgt
{
    class Scene {
    public:
        Scene(std::string pName);
        ~Scene();
        void update(float dt);
        void renderScene(VkCommandBuffer commandBuffer);
        std::string getName() { return name; }
        id_t getID() { return id; }
        World& getWorld() { return *_world; }
    private:
        id_t id;
        std::string name;
        World* _world = new World();

        Scene(const Scene&) = delete;
        Scene& operator= (const Scene&) = delete;
    };
}
#endif // SCENE_H