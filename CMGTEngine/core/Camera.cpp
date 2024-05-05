#pragma once
#include "Camera.hpp"

namespace cmgt {
	Camera::Camera(std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix, GameObject* pOwner) : Component(pOwner){
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
