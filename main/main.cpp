#include "core/Globals.h"
#include "utils/TestMaterial.h"
#include "utils/ObjectMovement.h"
#include "utils/CameraMovement.h"
#include "utils/MouseMovement.h"
#include "utils/ColorMaterial.h"
#include "core/Mesh.h"
#include "core/GraphicsPipeline.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/MeshCollider.h"
#include "physics-engine/SphereCollider.h"
#include "physics-engine/BoxCollider.h"
#include "physics-engine/PlaneCollider.h"
#include "minimal/types.h"
#include "core/Input.h"
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

cmgt::GameObject* SpawnPlane(glm::vec3 pos, glm::vec3 axis, float angle){
	cmgt::GameObject* planeObject = new cmgt::GameObject("Plane GameObject");
	planeObject->getTransform().Translate(pos);
	planeObject->getTransform().Scale(glm::vec3(10.f));
	planeObject->getTransform().Rotate(angle, axis);
	//planeObject->addComponent(new cmgt::Mesh("plane.obj", new cmgt::TestMaterial()));
	cmgt::Collider* planeColl = new cmgt::PlaneCollider();
	planeColl->setPhysType(cmgt::phys_type::STATIC);
	planeObject->addComponent(planeColl);

	return planeObject;
}

cmgt::GameObject* SpawnBall(glm::vec3 pos, glm::vec3 scale, glm::vec3 force){
	cmgt::GameObject* childObject = new cmgt::GameObject("Ball GameObject");
	childObject->getTransform().Translate(pos);
	childObject->getTransform().Scale(scale);
	cmgt::Mesh* cube = new cmgt::Mesh("sphere_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider = new cmgt::SphereCollider();
	collider->addForce(force, true);
	childObject->addComponent(cube);
	childObject->addComponent(collider);

	return childObject;
}

void OnGameStart(){
	physicsEngnie = new cmgt::PhysicsEngine();
	cmgt::Scene* firstScene = new cmgt::Scene("First Scene");

	firstScene->getWorld()->add(SpawnBall(glm::vec3(2, -2, 0), glm::vec3(1.f), glm::vec3(30,30,0)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(0, -4, 2), glm::vec3(1.f), glm::vec3(30,-30,0)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(4, -2, 0), glm::vec3(1.f), glm::vec3(30,30,30)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(6, -2, 2), glm::vec3(1.f), glm::vec3(0,30,30)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(2, -2, 2), glm::vec3(1.f), glm::vec3(0,30,-30)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(2, -2, 6), glm::vec3(1.f), glm::vec3(-30,30,0)));
	firstScene->getWorld()->add(SpawnBall(glm::vec3(6, -2, 6), glm::vec3(1.f), glm::vec3(0,30,0)));

	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -20, 0), glm::vec3(1,0,0), .0f));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, 0, 0), glm::vec3(1,0,0), glm::pi<float>()));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -10, 10), glm::vec3(1,0,0), -glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -10, -10), glm::vec3(1,0,0), glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(-10, -10, 0), glm::vec3(0,0,1), glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(10, -10, 0), glm::vec3(0,0,1), -glm::pi<float>() / 2));



	cmgt::GameObject* cameraObject = new cmgt::GameObject("Camera Object");
	cameraObject->getTransform().setMatrix(glm::mat4(+0.9,-0.0,-0.5,+0.0,
										 +0.3,+0.9,+0.4,+0.0,
										 +0.5,-0.5,+0.8,+0.0,
										 +2.0,-1.8,+3.2,+1.0 ));
	cmgt::Camera* camera = new cmgt::Camera();
	cameraObject->addComponent(camera);
	cameraObject->addComponent(new cmgt::CameraMovement(3.f,1.f));
	firstScene->getWorld()->setMainCamera(camera);
	firstScene->getWorld()->add(cameraObject);

	cmgt::SceneManager::get()->addScene(*firstScene);
}


void physics_loop(){

 	const cmgt::ms phys_step = cmgt::ms(1000 / (int)PHYSICS_STEP); // Time per iteration
	//const float phys_tick = PHYSICS_STEP / 1000.f;
	std::cout<<std::chrono::duration<float>(phys_step).count()<<std::endl;
    auto phys_clock = cmgt::clock::now();
		while (!cmgt::Window::get()->isOpened()) {	
			if(cmgt::clock::now() >= phys_clock){
				phys_clock += phys_step;
				float phys_tick = std::chrono::duration<float>(phys_clock - cmgt::clock::now()).count();
				std::cout<<phys_tick<<std::endl;
				if(cmgt::Input::isKeyPressed(GLFW_KEY_SPACE)){
					cmgt::SceneManager::physics_update(phys_tick);
					cmgt::PhysicsEngine::get()->phys_tick(phys_tick);
				}
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
		cmgt::SceneManager::update(_deltaTime);
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
