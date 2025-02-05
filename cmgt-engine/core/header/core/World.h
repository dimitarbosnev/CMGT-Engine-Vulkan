#ifndef WORLDSEED_H
#define WORLDSEED_H

#pragma once
#include "core/GameObject.h"
#include "core/Camera.h"
#include "core/Light.h"
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

		//only used internally, do not use from outside
		void registerLight(Light* pLight);
		void unregisterLight(Light* pLight);

		Light* getLightAt(int pIndex);
		int getLightCount();

	private:
		Camera* _mainCamera;
		std::vector<Light*> _lights;
		World& operator=(const World&);
		World(const World&);
	};
}
#endif // WORLDSEED_H