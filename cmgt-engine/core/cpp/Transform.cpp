
#include "core/Transform.h"
#include "core/GameObject.h"

namespace cmgt{
    void Transform::setLocalPosition(const glm::vec3& pPosition)  { getMatrix()[3] = glm::vec4(pPosition, 1); }

    void Transform::setWorldPosition(const glm::vec3& pPosition)  { 
        glm::mat4 newMatrix = matrix;
        newMatrix[3] = glm::vec4(pPosition, 1); 

        setWorldTransform(newMatrix);
    }

    void Transform::setWorldTransform(const glm::mat4& pMatrix){
        glm::mat4 newMatrix = pMatrix;
        if (_parent != nullptr) 
        newMatrix = glm::inverse(_parent->getTransform().getWorldTransform()) * pMatrix;

        setMatrix(newMatrix);
    }

    glm::vec3 Transform::getLocalPosition()	{ 
        return glm::vec3(getMatrix()[3]); 
    }
    glm::vec3 Transform::getScale() { 
        glm::mat4 newMatrix = getMatrix();
        glm::vec3 scale;
        scale.x = glm::length(glm::vec3(newMatrix[0]));
        scale.y = glm::length(glm::vec3(newMatrix[1]));
        scale.z = glm::length(glm::vec3(newMatrix[2]));
        return scale;
    }
    
    glm::vec3 Transform::getEulerRotation() {
        float x, y, z;
        glm::extractEulerAngleXYZ(getMatrix(),x,y,z);
        return glm::vec3(x,y,z);
    }

    glm::vec3 Transform::getWorldPosition(){
        return glm::vec3(getWorldTransform()[3]);
    }
    glm::mat4 Transform::getWorldTransform() {
        if (_parent == nullptr) return matrix;
        else return _parent->getTransform().getWorldTransform() * getMatrix();
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
    glm::mat3 Transform::getWorldRotationMatrix(){
        glm::mat4 worldTransform = getWorldTransform();
        return glm::mat3(
            glm::vec3(worldTransform[0]) / glm::length(worldTransform[0]),
            glm::vec3(worldTransform[1]) / glm::length(worldTransform[1]),
            glm::vec3(worldTransform[2]) / glm::length(worldTransform[2])
        );
    }

    glm::mat3 Transform::getLocalRotationMatrix(){
        glm::mat4 matrix = getMatrix();
        return glm::mat3(
            glm::vec3(matrix[0]) / glm::length(matrix[0]),
            glm::vec3(matrix[1]) / glm::length(matrix[1]),
            glm::vec3(matrix[2]) / glm::length(matrix[2])
        );
    }
    void Transform::Translate(const glm::vec3& pTranslation, bool ignoreRotation) {
        if(ignoreRotation)
            setLocalPosition(glm::vec3(getMatrix()[3]) - pTranslation);
        else
            setMatrix(glm::translate(getMatrix(), -pTranslation));
    }

    void Transform::Rotate(float pAngle, const glm::vec3& pAxis) {
        if(glm::length(pAxis) < 1){
            std::cout << "Invalid rotation axis" << std::endl;
            return;
        }
        setMatrix(glm::rotate(getMatrix(), pAngle, pAxis));
    }

    void Transform::Scale(const glm::vec3& pScale) {
        setMatrix(glm::scale(getMatrix(), pScale));
    }

    void Transform::WorldTranslate(const glm::vec3& pTranslation){
        glm::mat4 worldMatrix = getWorldTransform();

        setWorldPosition(glm::vec3(worldMatrix[3]) - pTranslation);
    }

}