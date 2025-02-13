#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "physics-engine/Collider.h"

namespace cmgt
{
	class SphereCollider : public Collider
	{
	public:

	public:
		SphereCollider();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
		void setRadius(float r) {radius = r;}
		//used in the SAT algorithm
		std::pair<float, float> getMinMaxValues(const Shape& shape, glm::vec3 axis) override;
		//used in the GJK/EPA algorithm
		glm::vec3 getFurthestPoint(const Shape& shape1,glm::vec3 dir) override;
		//used for checking rays intersections
		bool rayIntersectCheck(const glm::vec3& origin, const glm::vec3& dir, RayInfo* rayInfo) override;
	private:
		float radius = 1.f;
		//disallow copy and assignment
		SphereCollider(const Collider&);
		SphereCollider& operator=(const Collider&);
	};
} 
#endif // SPHERECOLLIDER_H