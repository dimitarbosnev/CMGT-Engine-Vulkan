#ifndef OBJECTMOVEMENT_HPP
#define OBJECTMOVEMENT_HPP

#pragma once
#include "Component.hpp"
namespace cmgt
{
	class GameObject;

	class ObjectMovement : public Component
	{
	public:

		ObjectMovement(float, float);
		void update(float) override;
	private:
		float _rotationSpeed;
		float _moveSpeed;
		//disallow copy and assignment
		ObjectMovement(const ObjectMovement&);
		ObjectMovement& operator=(const ObjectMovement&);
	};
} 
#endif // OBJECTMOVEMENT_HPP