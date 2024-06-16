#pragma once
#include "SceneManager.hpp"
#include "Scene.hpp"
namespace cmgt {
	void SceneManager::InitializesSceneManager() {
		assignInstance(new SceneManager());
	}

	SceneManager::~SceneManager() {
		while (!scenesStack.empty()) {
			scenesStack.pop();
		}
		for (auto &scene : scenes) {
			delete scene.second;
		}
		scenes.clear();
	}

	void SceneManager::update(float dt) {
		SceneManager& manager = getInstance();
		if (manager.scenesStack.size() != 0) {
			manager.scenesStack.top()->update(dt);
		}
		else
			cout << "There is no scene on the stack!" << endl;
	}

	void SceneManager::addScene(Scene& scene) {
		SceneManager& manager = getInstance();
		manager.scenes.emplace(scene.getID(), &scene);
		if (manager.scenes.size() == 1) {
			manager.gotoScene(scene);
		}
	}

	id_t SceneManager::assignSceneID()
	{
		SceneManager& sceneManager = getInstance();
		id_t i = 0;
		while (sceneManager.scenes.contains(i)) {
			i++;
		}
		return i;
	}

	void SceneManager::gotoScene(Scene& scene) {
		SceneManager& manager = getInstance();
		if (manager.scenes.contains(scene.getID()))
			manager.scenesStack.push(manager.scenes[scene.getID()]);
		else
			cout << "Scene does not exist on the stack!" << endl;;
	}

	void SceneManager::previousScene() { getInstance().scenesStack.pop(); }

	Scene& SceneManager::getScene(string name) {
		SceneManager& manager = getInstance();
		auto findByName = [name](const pair<id_t, Scene*>& a) { return a.second->getName() == name; };
		auto it = find_if(manager.scenes.begin(), manager.scenes.end(), findByName);
		return *it->second;
	}
	Scene& SceneManager::getScene(Scene& sceneID) { return getScene(sceneID.getID()); }
	Scene& SceneManager::getScene(id_t sceneID) { return *getInstance().scenes.find(sceneID)->second; }
	Scene& SceneManager::getCurrentScene() { return *getInstance().scenesStack.top(); }
}