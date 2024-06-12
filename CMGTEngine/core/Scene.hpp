#ifndef SCENE_HPP
#define SCENE_HPP

#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "GameObject.hpp"
#include "WorldSeed.hpp"

using namespace std;
using namespace glm;

namespace cmgt
{
    class Scene {
    public:
        Scene(string pName);
        ~Scene();
        void update(float dt);
        void renderScene(VkCommandBuffer commandBuffer);
        string getName() { return name; }
        id_t getID() { return id; }
        WorldSeed& getWorld() { return *_world; }
    private:
        id_t id;
        string name;
        WorldSeed* _world = new WorldSeed();

        Scene(const Scene&) = delete;
        Scene& operator= (const Scene&) = delete;
    };
}
#endif // SCENE_HPP