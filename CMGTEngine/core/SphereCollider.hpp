#ifndef SPHERECOLLIDER_HPP
#define SPHERECOLLIDER_HPP
#include "glm.hpp"
#include "Collider.hpp"
using namespace glm;
namespace cmgt
{
	class SphereCollider : public Collider
	{
	public:

	public:
		SphereCollider();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
	private:

		//disallow copy and assignment
		SphereCollider(const Collider&);
		SphereCollider& operator=(const Collider&);
	};
} 
#endif // SPHERECOLLIDER_HPP