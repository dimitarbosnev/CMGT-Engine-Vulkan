#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include "core/Object.h"
#include <string>
#include <vector>
#include <mutex>
namespace cmgt
{
	class World;
	class Component;
	class GameObject;
	//The transform could be an object but not sure for now
	class Transform {
	private:
		//to make this class thread safe functions for acsessing/writing the matrix getMantrix()/setMatrix()
		glm::mat4 matrix = glm::mat4(1);
		std::mutex matrix_lock;

		GameObject* _parent = nullptr;
		std::mutex parent_lock;
	public:
		void setLocalPosition(const glm::vec3& pPosition);
		//set the position in world space, SLOW use with care
		void setWorldPosition(const glm::vec3& pPosition);
		//set the transform in world space, SLOW use with care
		void setWorldTransform(const glm::mat4& newMatrix);
		glm::vec3 getLocalPosition();
		glm::vec3 getScale();
		glm::vec3 getEulerRotation();
		glm::mat4 getMatrix() { 
			std::lock_guard<std::mutex> lock(matrix_lock);
			return matrix; 
		}
		void setMatrix(const glm::mat4& newMatrix) { 
			std::lock_guard<std::mutex> lock(matrix_lock);
			matrix = newMatrix; 
		}
		//get the objects world position by combining transforms, SLOW use with care
		glm::vec3 getWorldPosition();
		//get the objects world position by combining transforms, SLOW use with care
		glm::mat4 getWorldTransform();
		//Transform a 4x4 matrix to world space NOTE: assumed pMatrix is in object space
		glm::mat4 toWorldSpace(const glm::mat4& pMatrix);
		void toWorldSpace(glm::mat4& pMatrix);
		//in local space
		void Translate(const glm::vec3& pTranslation);
		//in local space
		void Rotate(float pAngle,const glm::vec3& pAxis);
		//in local space
		void Scale(const glm::vec3& pScale);

		GameObject* getParent() {
			std::lock_guard<std::mutex> lock(parent_lock);
			return _parent;
		}

		void setParent(GameObject* pParent){
			std::lock_guard<std::mutex> lock(parent_lock);
			_parent = pParent;
		}

	};
}
#endif // TRANSFORM_H