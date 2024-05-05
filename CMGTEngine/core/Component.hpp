#pragma once
#include "../glm.hpp"
#include <string>
#include <vector>
#include "GameObject.hpp"
using namespace std;
using namespace glm;
namespace cmgt
{
    class Component
    {
    public:

        Component(GameObject* pOwner = nullptr);
        virtual ~Component() = 0;

        //for internal administration, do not use directly
        virtual void setOwner(GameObject* pGameObject);

        //behaviour should be able to update itself every step and MUST be implemented
        virtual void update(float pStep) = 0;
    protected:

        GameObject* _owner;

    private:

        //disallow copy and assignment
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
    };
}
