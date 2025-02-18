
#include "core/Light.h"
#include "core/GameObject.h"
#include "core/World.h"
#include "core/VulkanRenderer.h"
namespace cmgt {
	Light::Light(LightType type) {
	}

	Light::~Light() {}

	//Override setOwner to make sure we are registered
	//to the world we are a part of.
	void Light::OnSetOwner() {
		//if (pOwner == nullptr) return;
		//_owner->getWorld()->registerLight(this);
	}

	void Light::update(float pStep)
	{
		//diffrent types of light classes can be made
		LightStruct light;
		light.type = _type;
		light.color = _color;
		light.position = getTransform().getWorldPosition();
		light.direction = _direction;
		light.cut_off_angle = _cut_off_angle;
		light.intencity = _intencity;
		light.range = _range;

		//VulkanRenderer::get()->lights.
	}


}


