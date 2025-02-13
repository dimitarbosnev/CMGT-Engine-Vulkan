
#include "physics-engine/CapsuleCollider.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/Shape.h"
#include "core/GameObject.h"
namespace cmgt{

    CapsuleCollider::CapsuleCollider() : Collider(){
    }


    void CapsuleCollider::update(float pStep) {
    }

    std::pair<float, float> CapsuleCollider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {

        glm::mat3 rotationMatrix = getTransform().getWorldRotationMatrix();

        glm::vec3 worldOrientation = (rotationMatrix * orientation) * (height/2.f);

        glm::vec3 endpoint1 = shape.centroid + worldOrientation;
        glm::vec3 endpoint2 = shape.centroid - worldOrientation;

        float proj1 = glm::dot(endpoint1, axis);
        float proj2 = glm::dot(endpoint2, axis);

        float minProj = std::min(proj1, proj2) - radius;
        float maxProj = std::max(proj1, proj2) + radius;

        return {minProj, maxProj};
    }

    glm::vec3 CapsuleCollider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        //return the furthes vertex
        return  shape.worldTransform[3].xyz() + (dir * radius);
    }

    bool CapsuleCollider::rayIntersectCheck(const glm::vec3& S, const glm::vec3& d, RayInfo* rayInfo){
        //get the centroid

        glm::mat4 worldMatrix = getTransform().getWorldTransform();

        //leaving it here just in case it doesn't work out
        //std::vector<glm::vec3> worldMesh; worldMesh.reserve(colliderMesh.size());
        //for(const glm::vec3 vert : colliderMesh){
        //    worldMesh.push_back(worldMatrix*glm::vec4(vert,1));
        //}
        //glm::vec3 centroid = Shape::getCentroid(worldMesh);

        for(const Face& face : colliderFaces){
            //points on the triangle
            //S is the starting point of the ray
            //d is the direction of the ray
            glm::vec3 a = worldMatrix * glm::vec4(face.a(),1);
            glm::vec3 b = worldMatrix * glm::vec4(face.b(),1);
            glm::vec3 c = worldMatrix * glm::vec4(face.c(),1);
            //f = vector ab
            glm::vec3 e = b - a;
            //e = vector ac
            glm::vec3 f = c - a;
            //leaving it here just in case it doesn't work out
            //if(glm::dot(centroid,glm::cross(f,e)) > 0){
            //    glm::vec3 temp = f;
            //    f = e;
            //    e = temp;
            //}
            glm::vec3 q = glm::cross(e,d);     

            float D = glm::dot(f,q);
            if(D < 0) continue;
            
            glm::vec3 B = S - a;
            float B_q = glm::dot(B,q);
            if(B_q < 0 || B_q > D) continue;

            glm::vec3 p = glm::cross(f,B);
            float d_p = glm::dot(d,p);
            if(B_q + d_p < 0 || B_q + d_p > D) continue;

            float e_p = glm::dot(e,p);
            if(e_p < 0) continue;
            
            //If we got to here then we hit the face;
            float t = e_p / D;
            //Calculate the hit point and exit
            rayInfo->hitPoint = S + (t*d);

            return true;
        }   

        return false;
    }
}