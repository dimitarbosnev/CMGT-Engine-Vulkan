
#include "core/World.h"

namespace cmgt{

    void World::setMainCamera(Camera* pCamera) {
        if (pCamera != NULL) _mainCamera = pCamera;
    }

    Camera* World::getMainCamera() {
        return _mainCamera;
    }

    void World::registerLight(Light* pLight) {
        _lights.push_back(pLight);
    }

    void World::unregisterLight(Light* pLight) {
        if (_lights.size() == 0) return;
        _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
    }

    Light* World::getLightAt(int pIndex) {
        return _lights[pIndex];
    }

    int World::getLightCount() {
        return _lights.size();
    }
}