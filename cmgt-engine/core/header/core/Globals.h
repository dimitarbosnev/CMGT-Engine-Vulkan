#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once
#include "core/ObjectManager.h"
#include "core/SceneManager.h"
#include "core/VulkanRenderer.h"
#include "core/InputManager.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/Window.h"
#include "vulkan-api/VulkanSwapchain.h"
namespace cmgt {

	Window gameWindow(1600,900,"CMGT-Engnie");
    VulkanInstance vulkanInstance(&gameWindow);
    VulkanSwapchain vulkanSwapchain(vulkanInstance,gameWindow.getWindowExtend());
    VulkanRenderer vulkanRenderer(vulkanInstance, vulkanSwapchain, gameWindow);
    ObjectManager objectManager;
    SceneManager sceneManager;
    InputManager inputManager(gameWindow);
}
#endif //GLOBALS_H