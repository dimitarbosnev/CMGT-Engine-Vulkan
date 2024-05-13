#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#pragma once
#include "../glm.hpp"
#include "config.hpp"
#include <string>
#include <vector>
#include<map>
#include<stack>
using namespace std;
using namespace glm;

namespace cmgt
{
    class Scene;
    class SceneManager : public Singleton<SceneManager> {
    public:
        static void InitializesSceneManager();
        ~SceneManager();
        void update(float dt);
        void addScene(Scene& scene);
        void gotoScene(Scene& scene);
        void previousScene();
        Scene& getScene(string name);
        Scene& getScene(id_t sceneID);
        static id_t assignSceneID();

    private:
        map<id_t, Scene*> scenes;
        stack<Scene*> scenesStack;
        SceneManager() = default;

        SceneManager(const SceneManager&) = delete;
        SceneManager operator=(const SceneManager&) = delete;
    };
}
#endif // SCENEMANAGER_HPP