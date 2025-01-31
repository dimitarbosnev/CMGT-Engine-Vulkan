
#include "core/Camera.h"

namespace cmgt {
	Camera::Camera(glm::mat4 pProjectionMatrix) : _projection(pProjectionMatrix){
	}

	glm::mat4& Camera::getProjection() {
		return _projection;
	}
}
