#pragma once
#include "Component.hpp"

namespace cmgt{

    Component::Component() {
    }

    Component::~Component() {
    }

    void Component::setOwner(GameObject* pOwner) {
        _owner = pOwner;
    }

    void Component::update(float pStep) {}
}