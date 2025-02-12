#ifndef MOUSEMOVEMENT_H
#define MOUSEMOVEMENT_H

#pragma once
#include "core/Component.h"
namespace cmgt
{
	class GameObject;

	class MouseMovement : public Component
	{
	public:

	MouseMovement();
		void update(float) override;
	private:
		float _rotationSpeed;
		float _moveSpeed;
		//disallow copy and assignment
		MouseMovement(const MouseMovement&);
		MouseMovement& operator=(const MouseMovement&);
	};
} 
#endif // MOUSEMOVEMENT_H