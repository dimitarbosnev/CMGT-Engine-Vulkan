
#include "core/Camera.h"
#include "vulkan-api/Window.h"
namespace cmgt {
	Camera::Camera(glm::mat4 pProjectionMatrix) : _projection(pProjectionMatrix){
	}

	glm::mat4& Camera::getProjection() {
		return _projection;
	}

	glm::vec3 Camera::viewportToWorld(glm::vec2 coord){
        VkExtent2D extend = Window::get()->getWindowExtend();
        glm::vec2 windowSize = glm::vec2(extend.width,extend.height);
		glm::mat4 projectionMatrix = getProjection();
        //This is NDC space
        coord = ((glm::vec2(coord.x,coord.y) * 2.f) / windowSize) - 1.f;
        //This is view Space now
        glm::mat4 worldPos = getTransform().getWorldTransform();
        glm::mat4 viewMatrix = glm::inverse(worldPos);
        glm::vec3 mouseToWorld = glm::inverse(projectionMatrix * viewMatrix) * glm::vec4(coord,1,1);
        //This is world space
        glm::vec3 direction = glm::normalize(mouseToWorld);

		return direction;

	}
}
