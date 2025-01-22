
#include "core/WorldSeed.h"

namespace cmgt{

    void WorldSeed::setMainCamera(Camera* pCamera) {
        if (pCamera != NULL) _mainCamera = pCamera;
    }

    Camera* WorldSeed::getMainCamera() {
        return _mainCamera;
    }

    void WorldSeed::registerLight(Light* pLight) {
        _lights.push_back(pLight);
    }

    void WorldSeed::unregisterLight(Light* pLight) {
        if (_lights.size() == 0) return;
        _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
    }

    Light* WorldSeed::getLightAt(int pIndex) {
        return _lights[pIndex];
    }

    int WorldSeed::getLightCount() {
        return _lights.size();
    }
}