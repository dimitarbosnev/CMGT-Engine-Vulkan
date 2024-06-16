#pragma once
#include "Camera.hpp"

namespace cmgt {
	Camera::Camera(glm::mat4 pProjectionMatrix) {
	}

	glm::mat4& Camera::getProjection() {
		return _projection;
	}
}
