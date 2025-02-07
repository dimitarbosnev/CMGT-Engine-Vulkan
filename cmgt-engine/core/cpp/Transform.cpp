
#include "core/Transform.h"
#include "core/GameObject.h"

namespace cmgt{
    void Transform::setLocalPosition(glm::vec3 pPosition)  { matrix[3] = glm::vec4(pPosition, 1); }

    void Transform::setWorldPosition(glm::vec3 pPosition)  { 
        // maybe?
        glm::mat4 worldMatrix = matrix;
        worldMatrix[3] = glm::vec4(pPosition, 1); 

        if (_parent != nullptr) 
            worldMatrix = _parent->getTransform().getWorldTransform() * worldMatrix;
     
        matrix = worldMatrix;
    }
    glm::vec3 Transform::getLocalPosition()	{ 
        return glm::vec3(matrix[3]); 
    }
    glm::vec3 Transform::getScale() { 
        return glm::vec3(); 
    }
    
    glm::vec3 Transform::getEulerRotation() {
        glm::vec3 eulerAngles;
        glm::extractEulerAngleXYZ(matrix, eulerAngles.x, eulerAngles.y, eulerAngles.z);
        return eulerAngles; 
    }

    glm::vec3 Transform::getWorldPosition(){
        return glm::vec3(getWorldTransform()[3]);
    }
    glm::mat4 Transform::getWorldTransform() {
        if (_parent == nullptr) return matrix;
        else return _parent->getTransform().getWorldTransform() * matrix;
    };

    void Transform::Translate(glm::vec3 pTranslation) {
        matrix = glm::translate(matrix, pTranslation);
    }

    void Transform::Scale(glm::vec3 pScale) {
        matrix =glm::scale(matrix, pScale);
    }

    void Transform::Rotate(float pAngle, glm::vec3 pAxis) {
        matrix = glm::rotate(matrix, pAngle, pAxis);
    }
}