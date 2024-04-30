#include "FirstGame.hpp"
#include "../core/ShaderProgram.hpp"
#include "../core/config.hpp"
FirstGame::FirstGame(ivec2 resolution, string name, bool debug) : Game(resolution.x,resolution.y,name,debug) {

}

FirstGame::~FirstGame() {

}

void FirstGame::OnInit() {
	string vert = "vert.spv";
	string frag = "frag.spv";

	ShaderProgram* shader = new ShaderProgram(*gameAPI, vert, frag,ShaderProgram::defaultShaderProgramInfo(gameWindow->_width, gameWindow->_height));
}

void FirstGame::OnStart() {

}

void FirstGame::OnUpdate() {

}

void FirstGame::OnRender() {

}