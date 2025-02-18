#ifndef WORLDSEED_H
#define WORLDSEED_H

#pragma once
#include "core/GameObject.h"
#include "core/Camera.h"

namespace cmgt
{
	//class Camera;
	//class Light;

	class World : public GameObject
	{
	public:
		World() : GameObject("root"), _mainCamera(nullptr) { _world = this; }
		void setMainCamera(Camera* pCamera);
		Camera* getMainCamera();

	private:
		Camera* _mainCamera;
		World& operator=(const World&);
		World(const World&);
	};
}
#endif // WORLDSEED_H