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
#include "minimal/types.h"

namespace cmgt{
    void InitGlobals();
    void FreeGlobals();

    inline static int counter = 0;
    inline static int ticks = 1000;
    inline static us max_time = std::numeric_limits<us>::min();
    inline static us min_time = std::numeric_limits<us>::max();
    inline static us sum_time =  std::chrono::duration_cast<us>(clock::duration::zero());

    inline static double max_fps = std::numeric_limits<double>::min();
    inline static double min_fps = std::numeric_limits<double>::max();
    inline static double sum_fps = 0;
    inline static int fps_counter = 0;
}

#endif //GLOBALS_H