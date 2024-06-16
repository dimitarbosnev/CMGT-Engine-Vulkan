#pragma once
#include "Component.hpp"
#include "GameObject.hpp"
namespace cmgt{

    Component::Component() {
    }

    Component::~Component() {
    }

    void Component::setOwner(GameObject* pOwner) {
        _owner = pOwner;
    }

    void Component::update(float pStep) {}
    const glm::mat4& Component::getTransform() { return _owner->getTransform(); }
}