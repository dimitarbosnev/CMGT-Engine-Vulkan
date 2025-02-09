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
		void update(float pStep) override;
		
		//used in the SAT algorithm
		virtual std::pair<float, float> getMinMaxValues(const Shape& shape, glm::vec3 axis) override;
		//used in the GJK/EPA algorithm
		virtual glm::vec3 getFurthestPoint(const Shape& shape1,glm::vec3 dir) override;
	private:

		//disallow copy and assignment
		CapsuleCollider(const CapsuleCollider&);
		CapsuleCollider& operator=(const CapsuleCollider&);
	};
} 
#endif // CAPSULECOLLIDER_H