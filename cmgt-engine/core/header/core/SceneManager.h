#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma once
#include <string>
#include<map>
#include<stack>
#include "minimal/types.h"

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
        Scene* getScene(std::string name);
        Scene* getScene(id_t sceneID);

    private:
        id_t assignSceneID();
        std::map<id_t, Scene*> scenes;
        std::stack<Scene*> scenesStack;

        SceneManager(const SceneManager&) = delete;
        SceneManager operator=(const SceneManager&) = delete;
    };
}
#endif // SCENEMANAGER_H