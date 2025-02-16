#ifndef COLLIDER_H
#define COLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"
#include "minimal/types.h"
#include "core/Mesh.h"
#include "physics-engine/PhysicsBody.h"
#include <vector>
namespace cmgt
{
	struct Face{
		Face(glm::vec3 a, glm::vec3 b, glm::vec3 c){vertecies[0] = a; vertecies[1] = b; vertecies[2] = c;}
		glm::vec3 vertecies[3];
		const glm::vec3& a() const { return vertecies[0];}
		const glm::vec3& b() const { return vertecies[1];}
		const glm::vec3& c() const { return vertecies[2];}

		const glm::vec3& operator[] (uint32_t i){
			return vertecies[i];
		}
	};

	struct Shape;
	struct RayInfo;
	class Collider : public PhysicsBody
	{
	protected:
		glm::vec3 offset;
		glm::vec3 scale;
	public:
		Collider();
		virtual ~Collider();
		//behaviour should be able to update itself every step and MUST be implemented
		std::vector<Face> colliderFaces;
		std::vector<glm::vec3> colliderMesh;
		//used in the SAT algorithm
		virtual std::pair<float, float> getMinMaxValues(const Shape& shape, glm::vec3 axis);
		//used in the GJK/EPA algorithm
		virtual glm::vec3 getFurthestPoint(const Shape& shape1,glm::vec3 dir);
		//used for checking rays intersections
		virtual bool rayIntersectCheck(const glm::vec3& origin, const glm::vec3& dir, RayInfo* rayInfo);
		//used to comute the inertia tensor
		virtual void computeInertiaTensor();
	private:
		//disallow copy and assignment
		Collider(const Collider&);
		Collider& operator=(const Collider&);
	};
} 
#endif // COLLIDER_H