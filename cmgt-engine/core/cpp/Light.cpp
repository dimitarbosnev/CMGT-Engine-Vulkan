
#include "core/Light.h"
#include "core/GameObject.h"
#include "core/World.h"
#include "core/VulkanRenderer.h"
#include "minimal/log.h"
namespace cmgt {
	Light::Light(LightType type) : _type(type) {
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
		std::stringstream ss;
		ss << "Light type is: " << light.type;
		Log::msg(ss.str());
		light.intencity = _intencity;
		light.range = _range;
		light.color = _color;
		light.position = getTransform().getWorldPosition();
		light.direction = _direction;
		light.cut_off_angle = _cut_off_angle;
		VulkanRenderer::get()->scheduleLight(light);
	}


}


