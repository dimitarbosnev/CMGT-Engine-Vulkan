#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "physics-engine/Collider.h"

namespace cmgt
{
	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
	private:

		//disallow copy and assignment
		BoxCollider(const BoxCollider&);
		BoxCollider& operator=(const BoxCollider&);
	};
} 
#endif // BOXCOLLIDER_H