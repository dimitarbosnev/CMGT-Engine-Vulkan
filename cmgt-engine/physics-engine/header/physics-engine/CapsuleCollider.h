#ifndef CAPSULECOLLIDER_H
#define CAPSULECOLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "physics-engine/Collider.h"

namespace cmgt
{
	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider();
		//behaviour should be able to update itself every step and MUST be implemented
		void setRadius(float r) { radius = r; }
		void setHeight(float h) { height = h; }
		void setOrientation(glm::vec3 o) { orientation = glm::normalize(o); }
		//used in the SAT algorithm
		std::pair<float, float> getMinMaxValues(const Shape& shape, glm::vec3 axis) override;
		//used in the GJK/EPA algorithm
		glm::vec3 getFurthestPoint(const Shape& shape1,glm::vec3 dir) override;
		//used for checking rays intersections
		bool rayIntersectCheck(const glm::vec3& origin, const glm::vec3& dir, RayInfo* rayInfo) override;

		void computeInertiaTensor() override;
	private:
		float radius = 1.f;
		float height = 1.f;
		glm::vec3 orientation = glm::vec3(0,1,0);
		//disallow copy and assignment
		CapsuleCollider(const CapsuleCollider&);
		CapsuleCollider& operator=(const CapsuleCollider&);
	};
} 
#endif // CAPSULECOLLIDER_H