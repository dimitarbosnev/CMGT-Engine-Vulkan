#include "core/Window.h"
#include "core/ObjectManager.h"
#include "core/SceneManager.h"
#include "render-engine/VulkanInstance.h"
#include "render-engine/VulkanSwapchain.h"
#include "render-engine/VulkanRenderer.h"
#include <memory>
#include <string>

    cmgt::Window gameWindow(1600,900,"CMGT-Engnie");
    cmgt::VulkanInstance vulkanInstance(&gameWindow);
    cmgt::VulkanSwapchain vulkanSwapchain(vulkanInstance,gameWindow.getWindowExtend());
    cmgt::VulkanRenderer vulkanRenderer;
    cmgt::ObjectManager objectManager;
    cmgt::SceneManager sceneManager;


    int main() {
        //cmgt::Game* game = new FirstGame(ivec2(1600,900),"CMGTEngine");
        //try {
        //    game->run();
        //}
        //catch (const exception& e) {
        //    delete game;
        //    cerr << e.what() << endl;
        //    return EXIT_FAILURE;
        //}
        //delete game;
        //_CrtDumpMemoryLeaks();
        //return EXIT_SUCCESS;

        //Destroying Game
        vulkanSwapchain.destroySwapchain(vulkanInstance);
    }


