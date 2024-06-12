#pragma once
#include "Camera.hpp"

namespace cmgt {
	Camera::Camera(string pName, vec3 pPosition, mat4 pProjectionMatrix) {
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
