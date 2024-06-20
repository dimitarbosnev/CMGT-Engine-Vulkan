#ifndef CAMERA_HPP
#define CAMERA_HPP

#pragma once
#include <string>
#include "Component.hpp"
#include "glm.hpp"

using namespace std;
namespace cmgt {
    class Camera : public Component
    {
    public:
        Camera(glm::mat4 pProjectionMatrix = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
        glm::mat4& getProjection();

    private:
        glm::mat4 _projection;

        Camera(const Camera&);
        Camera& operator= (const Camera&);
    };
} 
#endif // CAMERA_HPP
