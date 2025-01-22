#ifndef OBJECTMOVEMENT_H
#define OBJECTMOVEMENT_H

#pragma once
#include "core/Component.h"
namespace cmgt
{
	class GameObject;

	class ObjectMovement : public Component
	{
	public:

		ObjectMovement(float pMoveSpeed = 1, float pRotationSpeed = 1);
		void update(float) override;
	private:
		float _rotationSpeed;
		float _moveSpeed;
		//disallow copy and assignment
		ObjectMovement(const ObjectMovement&);
		ObjectMovement& operator=(const ObjectMovement&);
	};
} 
#endif // OBJECTMOVEMENT_H