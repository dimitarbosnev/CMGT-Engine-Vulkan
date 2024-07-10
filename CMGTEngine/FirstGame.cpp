#pragma once
#include "FirstGame.hpp"
#include "core/ShaderProgram.hpp"
#include "core/config.hpp"
#include "core/Scene.hpp"
#include "core/SceneManager.hpp"
#include "core/Component.hpp"
#include "core/GameObject.hpp"
#include "core/Mesh.hpp"
#include "core/Light.hpp"
#include "core/Camera.hpp"
#include "core/CameraMovement.hpp"
#include "core/ObjectMovement.hpp"
FirstGame::FirstGame(ivec2 resolution, string name) : Game(resolution.x,resolution.y,name) {

}

FirstGame::~FirstGame() {

}
//View Matrix
/*
	+0.9,-0.0,-0.5,+0.0,
	+0.3,+0.9,+0.4,+0.0,
	+0.5,-0.5,+0.8,+0.0,
	+2.0,-1.8,+3.2,+1.0,
*/
void FirstGame::OnInit() {
	string vert = "vert.spv";
	string frag = "frag.spv";
	Scene* firstScene = new Scene("First Scene");

	GameObject* meshObject = new GameObject("First GameObject");
	meshObject->Scale(glm::vec3(1, -1, 1));
	meshObject->addComponent(Mesh::createModelFromFile("suzanna_smooth.obj"));
	meshObject->addComponent(new ObjectMovement(1, 1));
	firstScene->getWorld().add(meshObject);

	GameObject* meshObject2 = new GameObject("Second GameObject");
	meshObject2->Translate(glm::vec3(5, 0, 0));
	vector<Mesh::Vertex> vertecies{ {{0.0f,-0.5f,0.0f}, {1,0,0}},
									{{0.5f,0.5f,0.0f}, {0,1,0}},
									{{-0.5f,0.5f,0.0f},{0,0,1}} };
	meshObject2->addComponent(new Mesh(vertecies));
	firstScene->getWorld().add(meshObject2);

	GameObject* childObject = new GameObject("Child GameObject");
	childObject->Translate(glm::vec3(2, 1, 0));
	childObject->Scale(glm::vec3(.5f));
	childObject->addComponent(Mesh::createModelFromFile("cube_smooth.obj"));
	firstScene->getWorld().add(childObject);
	meshObject->add(childObject);

	GameObject* cameraObject = new GameObject("Camera Object");
	cameraObject->setTransform(glm::mat4(+0.9,-0.0,-0.5,+0.0,
										 +0.3,+0.9,+0.4,+0.0,
										 +0.5,-0.5,+0.8,+0.0,
										 +2.0,-1.8,+3.2,+1.0 ));
	Camera* camera = new Camera();
	cameraObject->addComponent(camera);
	cameraObject->addComponent(new CameraMovement(1,1));
	firstScene->getWorld().setMainCamera(camera);
	firstScene->getWorld().add(cameraObject);


	glm::mat4 cameraProj = camera->getProjection();
	glm::mat4 cameraTrans = glm::inverse(cameraObject->getWorldTransform());
	glm::mat4 meshTrans = meshObject->getTransform();
	glm::mat4 mvpMatrix = cameraProj * cameraTrans * meshTrans;
	cout << " M MATRIX: \n" << meshTrans << endl;
	cout << " V MATRIX: \n" << cameraTrans << endl;
	cout << " P MATRIX: \n" << cameraProj << endl;
	cout << " MVP MATRIX: \n" << mvpMatrix << endl;
	//ShaderProgram* shader = new ShaderProgram(*vulkanAPI, vert, frag, ShaderProgram::defaultShaderProgramInfo(gameWindow->Width, gameWindow->Height));
	//delete shader;
}

void FirstGame::OnStart() {

}

void FirstGame::OnUpdate() {

}

void FirstGame::OnRender() {

}

void FirstGame::OnExit(){

}
