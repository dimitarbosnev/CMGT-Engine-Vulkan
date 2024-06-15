#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "glm.hpp"
using namespace glm;
namespace cmgt
{
	class GameObject;

	class Component
	{
	public:

		Component();
		virtual ~Component();

		//for internal administration, do not use directly
		virtual void setOwner(GameObject* pGameObject);
		virtual const mat4& getTransform();
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep);
	protected:

		GameObject* _owner;

	private:

		//disallow copy and assignment
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
	};
} 
#endif // COMPONENT_HPP