#ifndef PLANECOLLIDER_HPP
#define PLANECOLLIDER_HPP
#include "glm.hpp"
#include "Collider.hpp"
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
#endif // PLANECOLLIDER_HPP