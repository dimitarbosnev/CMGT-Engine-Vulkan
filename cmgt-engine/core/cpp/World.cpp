
#include "core/World.h"

namespace cmgt{

    void World::setMainCamera(Camera* pCamera) {
        if (pCamera != NULL) _mainCamera = pCamera;
    }

    Camera* World::getMainCamera() {
        return _mainCamera;
    }
}