
#include "core/Light.h"
#include "core/GameObject.h"
#include "core/World.h"
namespace cmgt {
	Light::Light( LightType type) {
	}

	Light::~Light() {}

	//Override setOwner to make sure we are registered
	//to the world we are a part of.
	void Light::setOwner(GameObject* pOwner) {
		//if (pOwner == nullptr) return;
		Component::setOwner(pOwner);
		//_owner->getWorld()->registerLight(this);
	}

	void Light::update(float pStep)
	{
	}


}


