#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma once
#include <string>
#include<map>
#include<stack>
#include "minimal/types.h"
#include "core/Scene.h"
namespace cmgt
{
    //class Scene;
    class SceneManager : public Singelton<SceneManager>{
    public:
        SceneManager();
        ~SceneManager();
        static void update(float dt);
		static void physics_update(float phys_step);
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