#include "main/FirstGame.h"
#include <memory>
#include <string>
using namespace std;
using namespace glm;

    int main() {
        cmgt::Game* game = new FirstGame(ivec2(1600,900),"CMGTEngine");
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


