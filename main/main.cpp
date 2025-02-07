#include "core/Globals.h"
#include "utils/TestMaterial.h"
#include "utils/ObjectMovement.h"
#include "utils/CameraMovement.h"
#include "core/Mesh.h"
#include "core/GraphicsPipeline.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/Collider.h"
#include <memory>
#include <string>

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
	
		//cmgt::GameObject* meshObject2 = new cmgt::GameObject("Second GameObject");
		//meshObject2->getTransform().Translate(glm::vec3(5, 0, 0));
		//std::vector<cmgt::Vertex> vertecies{ {{0.0f,-0.5f,0.0f}, {1,0,0}},
		//							{{0.5f,0.5f,0.0f}, {0,1,0}},
		//							{{-0.5f,0.5f,0.0f},{0,0,1}} };
		//meshObject2->addComponent(new cmgt::Mesh(vertecies, new cmgt::TestMaterial()));
		//firstScene->getWorld()->add(meshObject2);

	//Collision Test 
	//Object 1
	//cmgt::GameObject* meshObject = new cmgt::GameObject("First GameObject");
	//meshObject->getTransform().Scale(glm::vec3(1, -1, 1));
	//cmgt::Mesh* monke = new cmgt::Mesh("suzanna_smooth.obj", new cmgt::TestMaterial());
	//meshObject->addComponent(monke);
	//meshObject->addComponent(new cmgt::ObjectMovement(.1f, .1f));
	//firstScene->getWorld()->add(meshObject);

	cmgt::GameObject* childObject = new cmgt::GameObject("Child GameObject");
	childObject->getTransform().Translate(glm::vec3(0, 0, 0));
	childObject->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider = new cmgt::Collider(cube->getVertexData());
	childObject->addComponent(cube);
	childObject->addComponent(collider);
	childObject->addComponent(new cmgt::ObjectMovement(1.f, 1.f));
	firstScene->getWorld()->add(childObject);
	//meshObject->add(childObject);

	//Objec2
	cmgt::GameObject* meshObject2 = new cmgt::GameObject("First GameObject");
	meshObject2->getTransform().Scale(glm::vec3(1, -1, 1));
	meshObject2->getTransform().Translate(glm::vec3(-4, 0, 0));
	cmgt::Mesh* monke2 = new cmgt::Mesh("suzanna_smooth.obj", new cmgt::TestMaterial());
	meshObject2->addComponent(monke2);
	//meshObject2->addComponent(new cmgt::ObjectMovement(.1f, .1f));
	firstScene->getWorld()->add(meshObject2);

	cmgt::GameObject* childObject2 = new cmgt::GameObject("Child GameObject");
	childObject2->getTransform().Translate(glm::vec3(0, 0, 0));
	childObject2->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube2 = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider2 = new cmgt::Collider(cube2->getVertexData());
	childObject2->addComponent(cube2);
	childObject2->addComponent(collider2);
	firstScene->getWorld()->add(childObject2);
	//meshObject2->add(childObject2);

	cmgt::GameObject* cameraObject = new cmgt::GameObject("Camera Object");
	cameraObject->getTransform().setMatrix(glm::mat4(+0.9,-0.0,-0.5,+0.0,
										 +0.3,+0.9,+0.4,+0.0,
										 +0.5,-0.5,+0.8,+0.0,
										 +2.0,-1.8,+3.2,+1.0 ));
	cmgt::Camera* camera = new cmgt::Camera();
	cameraObject->addComponent(camera);
	cameraObject->addComponent(new cmgt::CameraMovement(.1f,.1f));
	firstScene->getWorld()->setMainCamera(camera);
	firstScene->getWorld()->add(cameraObject);

	cmgt::SceneManager::get()->addScene(*firstScene);
	
	glm::mat4 cameraProj = camera->getProjection();
	glm::mat4 cameraTrans = glm::inverse(cameraObject->getTransform().getWorldTransform());
	//glm::mat4 meshTrans = meshObject->getTransform().getWorldTransform();
	//glm::mat4 mvpMatrix = cameraProj * cameraTrans * meshTrans;

	//cout << " M MATRIX: \n" << meshTrans << endl;
	//cout << " V MATRIX: \n" << cameraTrans << endl;
	//cout << " P MATRIX: \n" << cameraProj << endl;
	//cout << " MVP MATRIX: \n" << mvpMatrix << endl;
	//ShaderProgram* shader = new ShaderProgram(*vulkanAPI, vert, frag, ShaderProgram::defaultShaderProgramInfo(gameWindow->Width, gameWindow->Height));
	//delete shader;
}

int main() {
	cmgt::InitGlobals();
	//OnGameStart();

	physicsEngnie = new cmgt::PhysicsEngine();
	cmgt::Scene* firstScene = new cmgt::Scene("First Scene");
	
		//cmgt::GameObject* meshObject2 = new cmgt::GameObject("Second GameObject");
		//meshObject2->getTransform().Translate(glm::vec3(5, 0, 0));
		//std::vector<cmgt::Vertex> vertecies{ {{0.0f,-0.5f,0.0f}, {1,0,0}},
		//							{{0.5f,0.5f,0.0f}, {0,1,0}},
		//							{{-0.5f,0.5f,0.0f},{0,0,1}} };
		//meshObject2->addComponent(new cmgt::Mesh(vertecies, new cmgt::TestMaterial()));
		//firstScene->getWorld()->add(meshObject2);

	//Collision Test 
	//Object 1
	//cmgt::GameObject* meshObject = new cmgt::GameObject("First GameObject");
	//meshObject->getTransform().Scale(glm::vec3(1, -1, 1));
	//cmgt::Mesh* monke = new cmgt::Mesh("suzanna_smooth.obj", new cmgt::TestMaterial());
	//meshObject->addComponent(monke);
	//meshObject->addComponent(new cmgt::ObjectMovement(.1f, .1f));
	//firstScene->getWorld()->add(meshObject);

	cmgt::GameObject* childObject = new cmgt::GameObject("Child GameObject");
	childObject->getTransform().Translate(glm::vec3(0, 0, 0));
	childObject->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider = new cmgt::Collider(cube->getVertexData());
	childObject->addComponent(cube);
	childObject->addComponent(collider);
	childObject->addComponent(new cmgt::ObjectMovement(1.f, 1.f));
	firstScene->getWorld()->add(childObject);
	//meshObject->add(childObject);

	//Objec2
	//cmgt::GameObject* meshObject2 = new cmgt::GameObject("First GameObject");
	//meshObject2->getTransform().Scale(glm::vec3(1, -1, 1));
	//meshObject2->getTransform().Translate(glm::vec3(-4, 0, 0));
	//cmgt::Mesh* monke2 = new cmgt::Mesh("suzanna_smooth.obj", new cmgt::TestMaterial());
	//meshObject2->addComponent(monke2);
	////meshObject2->addComponent(new cmgt::ObjectMovement(.1f, .1f));
	//firstScene->getWorld()->add(meshObject2);

	cmgt::GameObject* childObject2 = new cmgt::GameObject("Child GameObject");
	childObject2->getTransform().Translate(glm::vec3(0, 0, 0));
	childObject2->getTransform().Scale(glm::vec3(.5f));
	cmgt::Mesh* cube2 = new cmgt::Mesh("cube_smooth.obj", new cmgt::TestMaterial());
	cmgt::Collider* collider2 = new cmgt::Collider(cube2->getVertexData());
	childObject2->addComponent(cube2);
	childObject2->addComponent(collider2);
	firstScene->getWorld()->add(childObject2);
	//meshObject2->add(childObject2);

	cmgt::GameObject* cameraObject = new cmgt::GameObject("Camera Object");
	cameraObject->getTransform().setMatrix(glm::mat4(+0.9,-0.0,-0.5,+0.0,
										 +0.3,+0.9,+0.4,+0.0,
										 +0.5,-0.5,+0.8,+0.0,
										 +2.0,-1.8,+3.2,+1.0 ));
	cmgt::Camera* camera = new cmgt::Camera();
	cameraObject->addComponent(camera);
	cameraObject->addComponent(new cmgt::CameraMovement(.1f,.1f));
	firstScene->getWorld()->setMainCamera(camera);
	firstScene->getWorld()->add(cameraObject);

	cmgt::SceneManager::get()->addScene(*firstScene);
	
	glm::mat4 cameraProj = camera->getProjection();
	glm::mat4 cameraTrans = glm::inverse(cameraObject->getTransform().getWorldTransform());
	//glm::mat4 meshTrans = meshObject->getTransform().getWorldTransform();
	//glm::mat4 mvpMatrix = cameraProj * cameraTrans * meshTrans;

	//cout << " M MATRIX: \n" << meshTrans << endl;
	//cout << " V MATRIX: \n" << cameraTrans << endl;
	//cout << " P MATRIX: \n" << cameraProj << endl;
	//cout << " MVP MATRIX: \n" << mvpMatrix << endl;
	//ShaderProgram* shader = new ShaderProgram(*vulkanAPI, vert, frag, ShaderProgram::defaultShaderProgramInfo(gameWindow->Width, gameWindow->Height));
	//delete shader;

	std::vector<cmgt::GameObject*> points(4);
	

    float lastTick = glfwGetTime();
		float second = 0;
		float fps = 0;
		while (!cmgt::Window::get()->isOpened()) {
			double time = glfwGetTime();
			float _deltaTime = (float)time - lastTick;
			lastTick = (float)time;
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
			//cmgt::PhysicsEngine::get()->update(_deltaTime);

			//Debug collision code
			cmgt::Shape shape1(collider), shape2(collider2);
			std::vector<glm::vec3> simplex = cmgt::PhysicsEngine::checkCollision(shape1,shape2);
			
			//Debug collision code end
			OnRender();
			cmgt::Camera* camera = cmgt::SceneManager::get()->getCurrentScene()->getWorld()->getMainCamera();
			glm::mat4 viewMatrix = camera->getTransform().getWorldTransform();
			glm::mat4 projectionMatrix = camera->getProjection();
			cmgt::VulkanRenderer::get()->drawFrame(viewMatrix,projectionMatrix);
		}
	vkDeviceWaitIdle(cmgt::VulkanInstance::get()->device());

    DestroyGame();
	cmgt::FreeGlobals();
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

//Make spawnObject in worldSeed
//Make newComponent and a manager for managing components
