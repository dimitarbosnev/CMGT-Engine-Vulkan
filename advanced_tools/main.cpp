#include "core/Globals.h"
#include "utils/TestMaterial.h"
#include "utils/ObjectMovement.h"
#include "utils/CameraMovement.h"
#include "utils/MouseMovement.h"
#include "utils/ColorMaterial.h"
#include "core/Mesh.h"
#include "core/Light.h"
#include "core/GraphicsPipeline.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/MeshCollider.h"
#include "physics-engine/SphereCollider.h"
#include "physics-engine/BoxCollider.h"
#include "physics-engine/PlaneCollider.h"
#include "minimal/types.h"
#include "core/Input.h"
#include "minimal/log.h"
#include <memory>
#include <string>
#include <thread>
#include <random>
	
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

cmgt::PhysicsEngine* physicsEngnie;
uint32_t num_of_colliders = 0;
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
	//planeObject->addComponent(new cmgt::Mesh("plane.obj", new cmgt::ColorMaterial()));
	cmgt::Collider* planeColl = new cmgt::PlaneCollider();
	planeColl->setPhysType(cmgt::phys_type::STATIC);
	planeObject->addComponent(planeColl);

	return planeObject;
}

cmgt::GameObject* SpawnBall(glm::vec3 pos, glm::vec3 scale, glm::vec3 force){
	cmgt::GameObject* childObject = new cmgt::GameObject("Ball GameObject");
	childObject->getTransform().Translate(pos);
	childObject->getTransform().Scale(scale);
	cmgt::Mesh* cube = new cmgt::Mesh("sphere_smooth.obj", new cmgt::ColorMaterial());
	cmgt::SphereCollider* collider = new cmgt::SphereCollider();
	collider->setRadius(scale.x);
	collider->addForce(force, true);
	childObject->addComponent(cube);
	childObject->addComponent(collider);

	return childObject;
}

void OnGameStart(){
	physicsEngnie = new cmgt::PhysicsEngine();
	cmgt::Scene* firstScene = new cmgt::Scene("First Scene");
	
	std::random_device rd;  
    // Use the Mersenne Twister engine
    std::mt19937 engine(rd());
	std::uniform_real_distribution<float> distrib_x(1.f, 9.f);
	std::uniform_real_distribution<float> distrib_y(-9.f, -1.f);
	std::uniform_real_distribution<float> distrib_z(1.f, 9.f);
	std::uniform_real_distribution<float> distrib_force_x(-20.f, 20.f);
	std::uniform_real_distribution<float> distrib_force_y(-20.f, 20.f);
	std::uniform_real_distribution<float> distrib_force_z(-20.f, 20.f);

	for(uint32_t i = 0; i < num_of_colliders; i++){
		float rand_x = distrib_x(engine);
		float rand_y = distrib_y(engine);
		float rand_z = distrib_z(engine);
		float rand_force_x = distrib_force_x(engine);
		float rand_force_y = distrib_force_y(engine);
		float rand_force_z = distrib_force_z(engine);
		firstScene->getWorld()->add(SpawnBall(glm::vec3(rand_x, rand_y, rand_z), glm::vec3(.3f), glm::vec3(rand_force_x,rand_force_y,rand_force_z)));
	}

	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -20, 0), glm::vec3(1,0,0), .0f));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, 0, 0), glm::vec3(1,0,0), glm::pi<float>()));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -10, 10), glm::vec3(1,0,0), -glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(0, -10, -10), glm::vec3(1,0,0), glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(-10, -10, 0), glm::vec3(0,0,1), glm::pi<float>() / 2));
	firstScene->getWorld()->add(SpawnPlane(glm::vec3(10, -10, 0), glm::vec3(0,0,1), -glm::pi<float>() / 2));

	{
		cmgt::GameObject* ambientLight = new cmgt::GameObject("Light Object");
		cmgt::Light* light_ambinet = new cmgt::Light();
		light_ambinet->setIntencity(0.3f);
		light_ambinet->setLightColor(glm::vec3(1, 1, 1));
		ambientLight->addComponent(light_ambinet);
		firstScene->getWorld()->add(ambientLight);
	}

	{
		cmgt::GameObject* dirLight = new cmgt::GameObject("Light Object");
		cmgt::Light* light_dir = new cmgt::Light(cmgt::LightType::Directional);
		light_dir->setIntencity(1.f);
		light_dir->setLightColor(glm::vec3(1, 1, 1));
		light_dir->setDirection(glm::normalize(glm::vec3(1, -1, 1)));
		dirLight->addComponent(light_dir);
		firstScene->getWorld()->add(dirLight);
	}

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

	std::stringstream ss;
	//ss << "Testing started setup: GJK / Sphere Collider / " << num_of_colliders;
	cmgt::Log::msg(ss.str());

	while (!cmgt::Window::get()->isOpened()) {	
		if(cmgt::clock::now() >= phys_clock){
			phys_clock += phys_step;
			float phys_tick = std::chrono::duration<float>(phys_clock - cmgt::clock::now()).count();
			//std::cout<<phys_tick<<std::endl;
			//if(cmgt::Input::isKeyPressed(GLFW_KEY_SPACE))
			{
				cmgt::SceneManager::physics_update(phys_tick);
				cmgt::PhysicsEngine::get()->phys_tick(phys_tick);
			}
		}
	}
}


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(200); //replase 200 with the coresponding number from the memory leack report :]
	cmgt::Log::init();
	cmgt::InitGlobals();
	OnGameStart();
	//std::thread physics_thread(physics_loop);
	const cmgt::ms fixed_game_step = cmgt::ms(1000 / TARGET_FPS); // Time per iteration

    auto game_clock = cmgt::clock::now();

	const cmgt::ms phys_step = cmgt::ms(1000 / (int)PHYSICS_STEP); // Time per iteration
    auto phys_clock = cmgt::clock::now();

	float second = 0;
	float fps = 0;

	std::stringstream ss;
	ss << "Testing started setup: algorithm: SAT / collider type: Mesh Collider / number of colliders: " << num_of_colliders << " / sample ticks: " << cmgt::ticks;
	cmgt::Log::msg(ss.str());

	while (!cmgt::Window::get()->isOpened()) {
		float _deltaTime = std::chrono::duration<float>(cmgt::clock::now() - game_clock).count();
		game_clock = cmgt::clock::now();

		if (second >= 1)
		{
			cmgt::sum_fps += fps;
			cmgt::fps_counter++;
			cmgt::max_fps = cmgt::max_fps < fps? fps : cmgt::max_fps;
			cmgt::min_fps = cmgt::min_fps > fps? fps : cmgt::min_fps;
			std::stringstream ss;
			ss << "FPS: " << fps;
			//cmgt::Log::msg(ss.str());
			second = 0;
			fps = 0;
			if(cmgt::Log::test_complete == true){
				float avg_fps = cmgt::sum_fps / cmgt::fps_counter;
				std::stringstream ss;
				ss << "Max fps is: " << cmgt::max_fps << " Min fps is: " << cmgt::min_fps << " Average fps is: " << avg_fps;
				cmgt::Log::msg(ss.str());
				cmgt::Log::test_complete = false;
				cmgt::Window::get()->close();
			}
		}
		else {
			second += _deltaTime;
			fps++;
		}

		OnUpdate();
		cmgt::SceneManager::update(_deltaTime);
		cmgt::Input::processInput();

		if(cmgt::clock::now() >= phys_clock){
			phys_clock += phys_step;
			float phys_tick = std::chrono::duration<float>(phys_clock - cmgt::clock::now()).count();
			cmgt::SceneManager::physics_update(phys_tick);
			cmgt::PhysicsEngine::get()->phys_tick(phys_tick);
		}

		OnRender();
		cmgt::Camera* camera = cmgt::SceneManager::get()->getCurrentScene()->getWorld()->getMainCamera();
		glm::mat4 viewMatrix = glm::inverse(camera->getTransform().getWorldTransform());
		glm::mat4 projectionMatrix = camera->getProjection();
		cmgt::VulkanRenderer::get()->drawFrame(viewMatrix,projectionMatrix);
	}

	//physics_thread.join();
	
	vkDeviceWaitIdle(cmgt::VulkanInstance::get()->device());

    DestroyGame();
	cmgt::FreeGlobals();
	cmgt::Log::close();
    return EXIT_SUCCESS;
}
