
#include "physics-engine/CapsuleCollider.h"
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/Shape.h"
#include "core/GameObject.h"
namespace cmgt{

    CapsuleCollider::CapsuleCollider() : Collider(){
        computeInertiaTensor();
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
        //implement capsule when I have to

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

    //it's copy paste from chat gpt, might not actually work
    void CapsuleCollider::computeInertiaTensor() {
    
        float volCyl = glm::pi<float>() * radius * radius * height;
        float volSph = 0.8f * glm::pi<float>() * radius * radius * radius;
        float totalVol = volCyl + volSph;
    
        // Mass distribution:
        float massCyl = getMass() * (volCyl / totalVol);
        float massSph = getMass() * (volSph / totalVol); // total mass for the full sphere
        float massHem = massSph / 2.0f;             // mass of one hemisphere
    
        // Cylinder inertia tensor about its center (aligned along z):
        float IzzCyl = 0.5f * massCyl * radius * radius;
        float IxxCyl = (1.0f / 12.0f) * massCyl * (3.0f * radius * radius + height * height);
        float IyyCyl = IxxCyl; // symmetric
    
        // Approximate inertia for a solid hemisphere about its own center of mass.
        // These numbers are approximate:
        float IperpHem_cm = 0.426f * massHem * radius * radius;  // about an axis in the plane of the flat face
        float IparallelHem_cm = 0.259f * massHem * radius * radius; // about the symmetry axis
    
        // Distance from capsule center to hemisphere center-of-mass.
        // The flat face of the hemisphere is at h/2 from the capsule center.
        // The center-of-mass of a hemisphere is located at 3r/8 from its flat face.
        float d = (height / 2.0f) + (3.0f * radius / 8.0f);
    
        // Apply parallel axis theorem for each hemisphere (for axes perpendicular to z):
        float IperpHem = IperpHem_cm + massHem * d * d;
    
        // Sum contributions:
        float Ixx = IxxCyl + 2.0f * IperpHem;
        float Iyy = IyyCyl + 2.0f * IperpHem;
        float Izz = IzzCyl + 2.0f * IparallelHem_cm;
        
        glm::mat3 inertia = glm::mat3(
            Ixx, 0.0f, 0.0f,
            0.0f, Iyy, 0.0f,
            0.0f, 0.0f, Izz
        );
        setInertiaTensor(inertia);
    }
}