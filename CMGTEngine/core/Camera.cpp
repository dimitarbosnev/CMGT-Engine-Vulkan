#pragma once
#include "Camera.hpp"

namespace cmgt {
	Camera::Camera(string pName, vec3 pPosition, mat4 pProjectionMatrix, GameObject* pOwner) : Component(pOwner){
	}

	Camera::~Camera()
	{
		//dtor
	}

	void Camera::update(float pStep)
	{
	}

	glm::mat4& Camera::getProjection() {
		return _projection;
	}
}
