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

		CameraMovement();
		void update(float pStep) override;
	private:

		//disallow copy and assignment
		CameraMovement(const CameraMovement&);
		CameraMovement& operator=(const CameraMovement&);
	};
} 
#endif // COMPONENT_HPP