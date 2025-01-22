#ifndef COLLIDER_H
#define COLLIDER_H
#include "core/glm.h"
#include "core/Component.h"
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
#endif // COLLIDER_H