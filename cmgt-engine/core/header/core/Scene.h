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
    class Scene : public Object {
    public:
        Scene(std::string pName);
        ~Scene();
        World* getWorld() { return _world; }

        void update(float pStep) override;
		void render(const VulkanFrameData& frameData) override;
		void physics_update(float phys_step) override;
    private:
        World* _world = new World();

        Scene(const Scene&) = delete;
        Scene& operator= (const Scene&) = delete;
    };
}
#endif // SCENE_H