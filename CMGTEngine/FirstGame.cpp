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
FirstGame::FirstGame(ivec2 resolution, string name) : Game(resolution.x,resolution.y,name) {

}

FirstGame::~FirstGame() {

}

void FirstGame::OnInit() {
	string vert = "vert.spv";
	string frag = "frag.spv";
	Scene* firstScene = new Scene("First Scene");

	GameObject* firstObject = new GameObject("First GameObject");

	firstObject->addComponent(*new Light());
	firstScene->getWorld().add(firstObject);
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
