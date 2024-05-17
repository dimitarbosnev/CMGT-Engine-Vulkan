#define GLFW_INCLUDE_VULKAN
#include "core/Game.hpp"
#include "Game/FirstGame.hpp"
#include <memory>
#include <string>
using namespace std;
using namespace glm;

    int main() {
        cmgt::Game* game = new FirstGame(ivec2(800,600),"CMGTEngine");
        try {
            game->run();
        }
        catch (const exception& e) {
            delete game;
            cerr << e.what() << endl;
            return EXIT_FAILURE;
        }
        delete game;
        _CrtDumpMemoryLeaks();
        return EXIT_SUCCESS;
    }


