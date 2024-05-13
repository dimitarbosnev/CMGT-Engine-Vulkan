#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#pragma once
#include "config.hpp"
#include <string>
#include<map>
#include<stack>
using namespace std;

namespace cmgt
{
    class Scene;
    class SceneManager : public Singleton<SceneManager>{
    public:
        static void InitializesSceneManager();
        ~SceneManager();
        static void update(float dt);
        static void addScene(Scene& scene);
        static void gotoScene(Scene& scene);
        static void previousScene();
        static Scene& getScene(string name);
        static Scene& getScene(Scene& sceneID);
        static Scene& getScene(id_t sceneID);
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