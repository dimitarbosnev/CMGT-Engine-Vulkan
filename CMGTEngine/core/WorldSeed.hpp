#pragma once
#include "GameObject.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <string>
#include <vector>
using namespace std;
using namespace glm;

class GmaeObject;
namespace cmgt
{
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
