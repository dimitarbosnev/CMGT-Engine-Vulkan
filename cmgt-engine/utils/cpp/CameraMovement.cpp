
#include "utils/CameraMovement.h"
#include "core/GameObject.h"
#include "core/Globals.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    CameraMovement::CameraMovement(float pMoveSpeed, float pRotationSpeed) : _moveSpeed(pMoveSpeed), _rotationSpeed(pRotationSpeed){
    }

    void CameraMovement::update(float pStep) {
        if (Input::isKeyPressed(GLFW_KEY_UP)) {
            _owner->getTransform().Translate(glm::vec3(0, 0, -_moveSpeed) * pStep);
            std::cout << _owner->getTransform().getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
            _owner->getTransform().Translate(glm::vec3(0, 0, _moveSpeed) * pStep);
            std::cout << _owner->getTransform().getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
            _owner->getTransform().Translate(glm::vec3(-_moveSpeed, 0, 0) * pStep);
            std::cout << _owner->getTransform().getWorldPosition() << std::endl;
        }
        if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
            _owner->getTransform().Translate(glm::vec3(_moveSpeed, 0, 0) * pStep);
            std::cout << _owner->getTransform().getWorldPosition() << std::endl;
        }
        if (Input::isMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            glm::vec2 deltaPos = Input::deltaMousePosition();
            _owner->getTransform().Rotate(deltaPos.x * pStep * _rotationSpeed, glm::vec3(0, -1, 0));
            _owner->getTransform().Rotate(deltaPos.y * pStep * _rotationSpeed, glm::vec3(1, 0, 0));
            //cout << "Camera Transform: \n" << _owner->getTransform() << endl;
            //cout << "Camera Rotation: \n" << currentRotation << endl;
        }
        //This is how you get the mouse to world
        glm::vec2 mousePos = Input::mousePosition();
        VkExtent2D extend = Window::get()->getWindowExtend();
        glm::vec2 windowSize = glm::vec2(extend.width,extend.height);
        cmgt::Camera* camera = cmgt::SceneManager::get()->getCurrentScene()->getWorld()->getMainCamera();
		glm::mat4 projectionMatrix = camera->getProjection();
        //This is NDC space
        mousePos = ((glm::vec2(mousePos.x,mousePos.y) * 2.f) / windowSize) - 1.f;
        mousePos = glm::vec2(mousePos.x,-mousePos.y);
        //This is view Space now
        glm::vec4 mouseToWorld = glm::inverse(projectionMatrix) * glm::vec4(mousePos,1,1);
        mouseToWorld = glm::vec4(mousePos,1,0);
        //This is world space
		glm::mat4 viewMatrix = camera->getTransform().getWorldTransform();
        glm::vec3 worldPos = getTransform().getLocalPosition();
        glm::vec3 direction = viewMatrix * mouseToWorld;
        direction = glm::normalize(direction);

        RayInfo info;
        if(PhysicsEngine::rayCast(worldPos, direction ,&info))
            std::cout << "RayCast WORKS!!!" << std::endl;

        //std::cout<<  direction <<std::endl;
        //std::cout<<  getTransform().getLocalRotationMatrix() * glm::vec3(0, 0, 1) <<std::endl;
        
        //cout << "Delta mouse pos: " << InputManager::deltaMousePosition() << " | Current mouse pos: " << InputManager::mousePosition() << endl;
    }
}