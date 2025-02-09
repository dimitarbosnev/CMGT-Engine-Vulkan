
#include "core/Component.h"
#include "core/GameObject.h"
namespace cmgt{

    Component::Component() {
    }

    Component::~Component() {
    }

    void Component::update(float pStep) {}

    Transform& Component::getTransform() { return _owner->getTransform(); }


    void Component::setOwner(GameObject* pOwner) {
        _owner = pOwner;
    }

    void Component::OnSetOwner(){
        
    }
}