#ifndef WORLDSEED_HPP
#define WORLDSEED_HPP

#pragma once
#include "../glm.hpp"
#include "GameObject.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace glm;

namespace cmgt
{
    class Camera;
    class Light;

    class WorldSeed : public GameObject
    {
    public:
        WorldSeed();

        void setMainCamera(Camera* pCamera);
        Camera* getMainCamera();

        //only used internally, do not use from outside
        void registerLight(Light* pLight);
        void unregisterLight(Light* pLight);

        Light* getLightAt(int pIndex);
        int getLightCount();

    private:
        Camera* _mainCamera;
        std::vector<Light*> _lights;

        WorldSeed(const WorldSeed&);
        WorldSeed& operator=(const WorldSeed&);
    };
}
#endif // WORLDSEED_HPP