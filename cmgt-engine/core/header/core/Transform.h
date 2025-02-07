#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include "core/Object.h"
#include <string>
#include <vector>

namespace cmgt
{
	class World;
	class Component;
	class GameObject;
	//The transform could be an object but not sure for now
	class Transform {
	private:
		friend class GameObject;
		glm::mat4 matrix = glm::mat4(1);
		GameObject* _parent = nullptr;
	public:
		void setLocalPosition(const glm::vec3 pPosition);
		//has to do some heavy computational work
		void setWorldPosition(const glm::vec3 pPosition);
		glm::vec3 getLocalPosition();
		glm::vec3 getScale();
		glm::vec3 getEulerRotation();
		glm::mat4 getMatrix() {return matrix; }
		void setMatrix(const glm::mat4& newMatrix) { matrix = newMatrix; }
		//get the objects world position by combining transforms, SLOW use with care
		glm::vec3 getWorldPosition();
		glm::mat4 getWorldTransform();
		//change LOCAL position, rotation, scaling
		void Translate(glm::vec3 pTranslation);
		void Rotate(float pAngle, glm::vec3 pAxis);
		void Scale(glm::vec3 pScale);

		const GameObject* getParent(){return _parent;}

	};
}
#endif // TRANSFORM_H