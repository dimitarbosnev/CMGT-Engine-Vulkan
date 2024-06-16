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
FirstGame::FirstGame(ivec2 resolution, string name) : Game(resolution.x,resolution.y,name) {

}

FirstGame::~FirstGame() {

}

void FirstGame::OnInit() {
	string vert = "vert.spv";
	string frag = "frag.spv";
	Scene* firstScene = new Scene("First Scene");
	GameObject* cameraObject = new GameObject("First GameObject");
	Camera* mainCamera = new Camera();
	cameraObject->addComponent(*mainCamera);
	firstScene->getWorld().setMainCamera(mainCamera);
	GameObject* meshObject = new GameObject("First GameObject");
	meshObject->addComponent(*Mesh::createModelFromFile("cube.obj"));
	meshObject->Translate(vec3(0, 0, 5));
	meshObject->Scale(vec3(0.5f, 0.5f, 0.5f));
	firstScene->getWorld().add(meshObject);
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
