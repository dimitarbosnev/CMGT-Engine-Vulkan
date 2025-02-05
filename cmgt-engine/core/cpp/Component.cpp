
#include "core/Component.h"
#include "core/GameObject.h"
namespace cmgt{

    Component::Component() {
    }

    Component::~Component() {
    }

    void Component::setOwner(GameObject* pOwner) {
        _owner = pOwner;
    }

    void Component::update(float pStep) {}
    glm::mat4 Component::getTransform() { return _owner->getWorldTransform(); }
}