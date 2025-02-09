#ifndef GLOBALS_H
#define GLOBALS_H

//use SAT for now it is more efficent over all and GJK/EPA has a problem with axis aligned objects giving weird collision normals
#define SAT

#pragma once
#include "core/ObjectManager.h"
#include "core/SceneManager.h"
#include "core/Input.h"
#include "core/VulkanRenderer.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/Window.h"
#include "vulkan-api/GLFW_Window.h"
#include "vulkan-api/VulkanSwapchain.h"

namespace cmgt{
    void InitGlobals();
    void FreeGlobals();
}

#endif //GLOBALS_H