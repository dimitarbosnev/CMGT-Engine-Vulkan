#include "core/Globals.h"

namespace cmgt {

	Window* gameWindow;//(1600,900,"CMGT-Engnie");                                     //
	VulkanInstance* vulkanInstance;//(&gameWindow);                                    //   
	VulkanSwapchain* vulkanSwapchain;//(vulkanInstance,gameWindow.getWindowExtend());  //
	VulkanRenderer* vulkanRenderer;//(vulkanInstance, vulkanSwapchain, gameWindow);    //
	ObjectManager* objectManager;                                                      // 
	SceneManager* sceneManager;          
                                                  //     
    void InitGlobals(){
        gameWindow = new GLFWindow(1280,720,"CMGT-Engnie");                            
        vulkanInstance = new VulkanInstance();                                      
        vulkanSwapchain = new VulkanSwapchain();  
        vulkanRenderer = new VulkanRenderer();    
        objectManager = new ObjectManager();                                                      
        sceneManager = new SceneManager();
		
		Input::InitInput();                                                        
    }

    void FreeGlobals(){
        delete sceneManager;
        delete objectManager;
        delete vulkanRenderer;
        delete vulkanSwapchain;
        delete vulkanInstance;
        delete gameWindow;
    }
}
