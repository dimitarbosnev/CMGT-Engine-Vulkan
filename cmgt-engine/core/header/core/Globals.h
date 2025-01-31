#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once
#include "core/Window.h"
#include "core/ObjectManager.h"
#include "core/SceneManager.h"
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanInstnace.h"
#include "vulkan-api/VulkanSwapchain.h"
namespace cmgt {

	Window gameWindow(1600,900,"CMGT-Engnie");
    VulkanInstance vulkanInstance(&gameWindow);
    VulkanSwapchain vulkanSwapchain(vulkanInstance,gameWindow.getWindowExtend());
    VulkanRenderer vulkanRenderer;
    ObjectManager objectManager;
    SceneManager sceneManager;
}
#endif //GLOBALS_H