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
FirstGame::FirstGame(ivec2 resolution, string name) : Game(resolution.x,resolution.y,name) {

}

FirstGame::~FirstGame() {

}

void FirstGame::OnInit() {
	string vert = "vert.spv";
	string frag = "frag.spv";
	Scene* firstScene = new Scene("First Scene");

	GameObject* meshObject = new GameObject("First GameObject");
	meshObject->addComponent(Mesh::createModelFromFile("cube.obj"));

	GameObject* camerObject = new GameObject("Camera Object");
	Camera* camera = new Camera();
	camerObject->addComponent(camera);
	camerObject->addComponent(new CameraMovement());
	firstScene->getWorld().setMainCamera(camera);
	firstScene->getWorld().add(meshObject);
	firstScene->getWorld().add(camerObject);
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
