#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "physics-engine/Collider.h"

namespace cmgt
{
	class PlaneCollider : public Collider
	{
	public:

	public:
		PlaneCollider();

	private:

		//disallow copy and assignment
		PlaneCollider(const PlaneCollider&);
		PlaneCollider& operator=(const PlaneCollider&);
	};
} 
#endif // PLANECOLLIDER_H