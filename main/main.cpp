#include "core/Globals.h"
#include "utils/TestMaterial.h"
#include "utils/ObjectMovement.h"
#include "utils/CameraMovement.h"
#include "utils/MouseMovement.h"
#include "core/Mesh.h"
#include "core/GraphicsPipeline.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/MeshCollider.h"
#include "physics-engine/SphereCollider.h"
#include "physics-engine/BoxCollider.h"
#include "minimal/types.h"
#include <memory>
#include <string>
#include <thread>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

cmgt::PhysicsEngine* physicsEngnie;
void DestroyGame(){
	//if(cmgt::TestMaterial::pipeline)
		//delete cmgt::TestMaterial::pipeline;
	delete physicsEngnie;
	std::cout << "Game destroyed\n";
}

void OnUpdate(){

}

void OnRender(){
    
}

void OnGameStart(){
	physicsEngnie = new cmgt::PhysicsEngine();
	cmgt::Scene* firstScene = new cmgt::Scene("First Scene");

	cmgt::GameObject* childObject = new cmgt::GameObject("Child GameObject");
	childObject->getTransform().Translate(glm::vec3(2, 0, 0));
	childObject->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider = new cmgt::BoxCollider();
	childObject->addComponent(cube);
	childObject->addComponent(collider);
	childObject->addComponent(new cmgt::ObjectMovement(2.f, 2.f));
	firstScene->getWorld()->add(childObject);

	cmgt::GameObject* childObject2 = new cmgt::GameObject("Child GameObject2");
	childObject2->getTransform().Translate(glm::vec3(0, 0, 0));
	childObject2->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube2 = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider2 = new cmgt::MeshCollider(cube2->getVertexData());
	childObject2->addComponent(cube2);
	childObject2->addComponent(collider2);
	firstScene->getWorld()->add(childObject2);

	//cmgt::GameObject* mousedObject = new cmgt::GameObject("Child GameObject");
	//mousedObject->getTransform().Translate(glm::vec3(0, 0, 0));
	//mousedObject->getTransform().Scale(glm::vec3(.5f));
	//mousedObject->addComponent(new cmgt::Mesh("sphere_smooth.obj", new cmgt::TestMaterial()));
	//mousedObject->addComponent(new cmgt::MouseMovement());
	//firstScene->getWorld()->add(mousedObject);

	cmgt::GameObject* cameraObject = new cmgt::GameObject("Camera Object");
	cameraObject->getTransform().setMatrix(glm::mat4(+0.9,-0.0,-0.5,+0.0,
										 +0.3,+0.9,+0.4,+0.0,
										 +0.5,-0.5,+0.8,+0.0,
										 +2.0,-1.8,+3.2,+1.0 ));
	cmgt::Camera* camera = new cmgt::Camera();
	cameraObject->addComponent(camera);
	cameraObject->addComponent(new cmgt::CameraMovement(1.f,1.f));
	firstScene->getWorld()->setMainCamera(camera);
	firstScene->getWorld()->add(cameraObject);

	cmgt::SceneManager::get()->addScene(*firstScene);
}


void physics_loop(){

 const cmgt::ms phys_step = cmgt::ms(1000 / PHYSICS_STEP); // Time per iteration

    auto phys_clock = cmgt::clock::now();
		while (!cmgt::Window::get()->isOpened()) {	
			if(cmgt::clock::now() >= phys_clock){
				phys_clock += phys_step;
				float phys_tick = std::chrono::duration<float>(cmgt::clock::now() - phys_clock).count();
				cmgt::PhysicsEngine::get()->update(phys_tick);
			}
		}
}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(200); //replase 200 with the coresponding number from the memory leack report :]
	cmgt::InitGlobals();
	OnGameStart();
	std::thread physics_thread(physics_loop);
	const cmgt::ms fixed_game_step = cmgt::ms(1000 / TARGET_FPS); // Time per iteration

    auto game_clock = cmgt::clock::now();

	float second = 0;
	float fps = 0;
	while (!cmgt::Window::get()->isOpened()) {
		float _deltaTime = std::chrono::duration<float>(cmgt::clock::now() - game_clock).count();
		game_clock = cmgt::clock::now();

		if (second >= 1)
		{
			std::cout << "FPS: " << fps << std::endl;
			second = 0;
			fps = 0;
		}
		else {
			second += _deltaTime;
			fps++;
		}

		OnUpdate();
		cmgt::SceneManager::get()->update(_deltaTime);
		cmgt::Input::processInput();

		OnRender();
		cmgt::Camera* camera = cmgt::SceneManager::get()->getCurrentScene()->getWorld()->getMainCamera();
		glm::mat4 viewMatrix = glm::inverse(camera->getTransform().getWorldTransform());
		glm::mat4 projectionMatrix = camera->getProjection();
		cmgt::VulkanRenderer::get()->drawFrame(viewMatrix,projectionMatrix);
	}

	physics_thread.join();
	
	vkDeviceWaitIdle(cmgt::VulkanInstance::get()->device());

    DestroyGame();
	cmgt::FreeGlobals();
    return EXIT_SUCCESS;
}
