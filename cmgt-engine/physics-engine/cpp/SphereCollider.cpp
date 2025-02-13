
#include "physics-engine/SphereCollider.h"
#include"physics-engine/Shape.h"
#include"core/GameObject.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    SphereCollider::SphereCollider() : Collider(){
    }


    void SphereCollider::update(float pStep) {
    }

    std::pair<float, float> SphereCollider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {
        // Initialize with extreme values
        float dot = glm::dot(shape.centroid, axis);
        float minProj = dot - radius;
        float maxProj = dot + radius;

        return {minProj, maxProj};
    }

    glm::vec3 SphereCollider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        //return the furthes vertex
        return  shape.worldTransform[3].xyz() + (dir * radius);
    }

    bool SphereCollider::rayIntersectCheck(const glm::vec3& o, const glm::vec3& d, RayInfo* rayInfo){

        //cs = worldPosition
        //p = point on the sphere
        //r = radius
        //o = ray origin point
        //d = ray direction
        //t = time variable that we gonna examine and try and find

        //ray is defined by ray=o+dt
        //Sphere is defigned by (p-cs)^2 = r^2

        //intersection equasion is p = o+dt

        glm::mat4 worldMatrix = getTransform().getWorldTransform();
        glm::vec3 cs = worldMatrix[3];
        glm::vec3 v = o-cs;

        //euqasion is (o+dt-c)^2 = r^2
        //replace o-c with v (v+dt)^2 = r^2
        //expand v^2+2vdt+d^2t^2 = r^2
        //qudratic at^2 + bt + c = 0
        //a = d^2
        float a = glm::dot(d,d);
        //b = 2vd
        float b = 2 * glm::dot(v,d);
        //c = v^2 - r^2
        float c = glm::dot(v,v) - std::pow(radius,2);

        float D = std::pow(b,2) - (4 * a * c);

        if(D < 0) return false;

        float t = 0;
        float e = 2*a;
        float f = -b / e;

        if(D == 0){
            //t = -b / 2*a
            t = f;
        }
        else{
            float p = D / e;
            //t1 = -b - D / 2*a
            float t1 = f - p;
            //t2 = b + D / 2*a
            float t2 = f + p;
            //t is the one smaller
            //and should potentially be positive
            t = t1 < t2 ? t1 : t2;
        }

        rayInfo->hitPoint = o + (t*d);
        return true;
    }
}