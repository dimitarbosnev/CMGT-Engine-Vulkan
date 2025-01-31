#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma once
#include <string>
#include<map>
#include<stack>
#include "minimal/types.h"
using namespace std;

namespace cmgt
{
    class Scene;
    class SceneManager {
    public:
        SceneManager();
        ~SceneManager();
        void update(float dt);
        void addScene(Scene& scene);
        void gotoScene(Scene& scene);
        void previousScene();
        Scene* getCurrentScene();
        Scene* getScene(string name);
        Scene* getScene(id_t sceneID);

    private:
        id_t assignSceneID();
        map<id_t, Scene*> scenes;
        stack<Scene*> scenesStack;

        SceneManager(const SceneManager&) = delete;
        SceneManager operator=(const SceneManager&) = delete;
    };
}
#endif // SCENEMANAGER_H