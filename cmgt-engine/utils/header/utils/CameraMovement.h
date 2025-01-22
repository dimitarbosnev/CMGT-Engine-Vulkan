#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

#pragma once
#include "core/Component.h"
namespace cmgt
{
	class GameObject;

	class CameraMovement : public Component
	{
	public:

		CameraMovement(float pMoveSpeed = 1, float pRotationSpeed = 1);
		void update(float) override;
	private:
		float _rotationSpeed;
		float _moveSpeed;
		//disallow copy and assignment
		CameraMovement(const CameraMovement&);
		CameraMovement& operator=(const CameraMovement&);
	};
} 
#endif // COMPONENT_H