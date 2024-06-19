#ifndef CAMERAMOVEMENT_HPP
#define CAMERAMOVEMENT_HPP

#pragma once
#include "Component.hpp"
namespace cmgt
{
	class GameObject;

	class CameraMovement : public Component
	{
	public:

		CameraMovement(float, float);
		void update(float) override;
	private:
		float _rotationSpeed;
		float _moveSpeed;
		//disallow copy and assignment
		CameraMovement(const CameraMovement&);
		CameraMovement& operator=(const CameraMovement&);
	};
} 
#endif // COMPONENT_HPP