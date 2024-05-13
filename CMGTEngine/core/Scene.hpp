#ifndef SCENE_HPP
#define SCENE_HPP

#pragma once
#include "../glm.hpp"
#include "GameObject.hpp"
#include "WorldSeed.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace glm;

namespace cmgt
{
    class Scene {
    public:
        Scene(string pName);
        ~Scene();
        void update(float dt);
        void renderScene();
        string getName() { return name; }
        id_t getID() { return id; }
    private:
        id_t id;
        string name;
        WorldSeed _world{};

        Scene(const Scene&) = delete;
        Scene& operator= (const Scene&) = delete;
    };
}
#endif // SCENE_HPP