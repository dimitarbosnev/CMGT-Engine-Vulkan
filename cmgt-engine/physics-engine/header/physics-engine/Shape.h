#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"
#include "minimal/types.h"
#include "core/Mesh.h"
#include "physics-engine/Collider.h"
#include <vector>
namespace cmgt
{
	struct Shape{
		Shape(Collider*pCollider);
		std::vector<glm::vec3> colliderMesh;
		glm::mat4 worldTransform;
		glm::vec3 centroid;

		static glm::vec3 getCentroid(const std::vector<glm::vec3>& vertecies);
		//used in the SAT algorithm
		std::pair<float, float> getMinMaxValues(glm::vec3 axis) const { return collider->getMinMaxValues(*this, axis);}
		//used in the GJK/EPA algorithm
		glm::vec3 getFurthestPoint(glm::vec3 dir) const { return collider->getFurthestPoint(*this,dir);}

	private: 
		Collider* collider;
	};
} 
#endif // SHAPE_H