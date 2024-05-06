#pragma once
#include "Component.hpp"

namespace cmgt{

    Component::Component(GameObject* pOwner) {
        setOwner(pOwner);
    }

    Component::~Component() {
    }

    void Component::setOwner(GameObject* pOwner) {
        _owner = pOwner;
    }

    void Component::update(float pStep) {}
}