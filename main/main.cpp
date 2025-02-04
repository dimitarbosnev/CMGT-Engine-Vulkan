#include "core/Globals.h"
#include "utils/TestMaterial.h"
#include <memory>
#include <string>

void DestroyGame(){
	delete &cmgt::TestMaterial::pipeline;
	std::cout << "Game destroyed\n";
}

void OnUpdate(){

}

void OnRender(){
    
}
int main() {
	cmgt::InitGlobals();

    float lastTick = glfwGetTime();
		float second = 0;
		float fps = 0;
		while (!cmgt::gameWindow->isOpened()) {
			double time = glfwGetTime();
			float _deltaTime = (float)time - lastTick;
			lastTick = (float)time;
			if (second >= 1)
			{
				std::cout << "FPS: " << fps << std::endl;
				second = 0;
				fps = 0;
			}
			else {
				second += _deltaTime;
				fps++;
			}
			OnUpdate();
			cmgt::sceneManager->update(_deltaTime);
			OnRender();
			cmgt::vulkanRenderer->drawFrame();
		}

    DestroyGame();
	cmgt::FreeGlobals();
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

