#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H
#include "minimal/glm.h"
#include "physics-engine/Collider.h"
using namespace glm;
namespace cmgt
{
	class PlaneCollider : public Collider
	{
	public:

	public:
		PlaneCollider();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
	private:

		//disallow copy and assignment
		PlaneCollider(const PlaneCollider&);
		PlaneCollider& operator=(const PlaneCollider&);
	};
} 
#endif // PLANECOLLIDER_H