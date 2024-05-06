#ifndef CAMERA_HPP
#define CAMERA_HPP


#pragma once
#include <string>
#include "Component.hpp"
#include "../glm.hpp"


using namespace std;
using namespace glm;
namespace cmgt {
    class GmaeObject;
    class Camera : public Component
    {
    public:
        Camera(
            string pName = "camera",
            vec3 pPosition = vec3(0.0f, 3.0f, 5.0f),
            mat4 pProjectionMatrix = perspective(radians(70.0f), 4.0f / 3.0f, 0.1f, 1000.0f),
            GameObject* pOwner = nullptr
        );

        virtual ~Camera() override;
        virtual void update(float pStep) override;
        mat4& getProjection();

    private:
        mat4 _projection;

    private:
        Camera(const Camera&) = delete;
        Camera& operator= (const Camera&) = delete;
    };
} 
#endif // CAMERA_HPP
