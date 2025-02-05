
#include "core/SceneManager.h"
#include "core/Scene.h"
namespace cmgt {

	SceneManager::SceneManager() : Singelton<SceneManager>(this) {
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
		if (scenesStack.size() != 0) {
			scenesStack.top()->update(dt);
		}
		else
			std::cout << "There is no scene on the stack!" << std::endl;
	}

	void SceneManager::addScene(Scene& scene) {
		scenes.emplace(scene.getID(), &scene);
		if (scenes.size() == 1) {
			gotoScene(scene);
		}
	}

	id_t SceneManager::assignSceneID()
	{
		id_t i = 0;
		while (scenes.contains(i)) {
			i++;
		}
		return i;
	}

	void SceneManager::gotoScene(Scene& scene) {
		if (scenes.contains(scene.getID()))
			scenesStack.push(scenes[scene.getID()]);
		else
			std::cout << "Scene does not exist on the stack!" << std::endl;;
	}

	void SceneManager::previousScene() { scenesStack.pop(); }

	Scene* SceneManager::getCurrentScene()
	{
		assert(scenesStack.size() != 0 && "There is no scene on the stack!");
		return scenesStack.top();
	}

	Scene* SceneManager::getScene(std::string name) {
		auto findByName = [name](const std::pair<id_t, Scene*>& a) { return a.second->getName() == name; };
		auto it = find_if(scenes.begin(), scenes.end(), findByName);
		return it->second;
	}
	Scene* SceneManager::getScene(id_t sceneID) { return scenes.find(sceneID)->second; }
}