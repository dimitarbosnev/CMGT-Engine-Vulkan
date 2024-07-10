#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "glm.hpp"
#include "Component.hpp"
using namespace glm;
namespace cmgt
{
	class Collider : public Component
	{
	protected:
		glm::vec3 offset;
		glm::vec3 scale;
	public:
		Collider();
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep) override;
	private:

		//disallow copy and assignment
		Collider(const Collider&);
		Collider& operator=(const Collider&);
	};
} 
#endif // COLLIDER_HPP