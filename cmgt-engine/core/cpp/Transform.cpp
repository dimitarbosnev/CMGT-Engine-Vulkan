
#include "core/Transform.h"
#include "core/GameObject.h"

namespace cmgt{
    void Transform::setLocalPosition(const glm::vec3& pPosition)  { matrix[3] = glm::vec4(pPosition, 1); }

    void Transform::setWorldPosition(const glm::vec3& pPosition)  { 
        glm::mat4 newMatrix = matrix;
        newMatrix[3] = glm::vec4(pPosition, 1); 

        if (_parent != nullptr) 
        matrix = _parent->getTransform().getWorldTransform() * newMatrix;
     
    }
    void Transform::setWorldTransform(const glm::mat4& newMatrix){
        if (_parent != nullptr) 
        matrix = _parent->getTransform().getWorldTransform() * newMatrix;
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

    glm::mat4 Transform::toWorldSpace(const glm::mat4& pMatrix){
        glm::mat4 newMatrix;
        if (_parent != nullptr) 
        newMatrix = _parent->getTransform().getWorldTransform() * pMatrix;
     
        return newMatrix;
    }

    void Transform::toWorldSpace(glm::mat4& pMatrix){
        if (_parent != nullptr) 
        pMatrix = _parent->getTransform().getWorldTransform() * pMatrix;
    }

    void Transform::Translate(const glm::vec3& pTranslation) {
        matrix = glm::translate(matrix, pTranslation);
    }

    void Transform::Rotate(float pAngle, const glm::vec3& pAxis) {
        matrix = glm::rotate(matrix, pAngle, pAxis);
    }

    void Transform::Scale(const glm::vec3& pScale) {
        matrix = glm::scale(matrix, pScale);
    }

}