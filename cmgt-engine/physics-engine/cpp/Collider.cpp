
#include "physics-engine/Collider.h"
#include "core/GameObject.h"
#include "physics-engine/Shape.h"
#include "physics-engine/PhysicsEngine.h"
namespace cmgt{

    Collider::Collider() {
        PhysicsEngine::get()->addCollider(this);
    }

    Collider::~Collider(){
        colliderMesh.clear();
    }

    std::pair<float, float> Collider::getMinMaxValues(const Shape& shape, glm::vec3 axis) {
        // Initialize with extreme values
        float minProj = MAX;
        float maxProj = -MAX;

        for (const glm::vec3& vert : shape.colliderMesh) {
            //projection
            float proj = glm::dot(vert, axis);
            minProj = std::min(minProj, proj);
            maxProj = std::max(maxProj, proj);
        }

        return {minProj, maxProj};
    }

    glm::vec3 Collider::getFurthestPoint(const Shape &shape, glm::vec3 dir) {
        //might be usefult to add in centroid space
        dir = glm::normalize(dir);

        glm::vec3 furthestVert;
        float value = -MAX;
        for (glm::vec3 vert : shape.colliderMesh)
        {
            float temp = glm::dot(vert, dir);
            if (temp > value)
            {
                furthestVert = vert;
                value = temp;
            }
        }

        //return the furthes vertex
        return  furthestVert;
    }

    bool Collider::rayIntersectCheck(const glm::vec3& S, const glm::vec3& d, RayInfo* rayInfo){
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

    void Collider::computeInertiaTensor() {
        glm::mat3 inertia(0.0f);
    
        // Assume equal mass per vertex.
        float perVertexMass = getMass() / static_cast<float>(colliderMesh.size());
    
        for (const glm::vec3& v : colliderMesh) {
            float x = v.x, y = v.y, z = v.z;
            inertia[0][0] += perVertexMass * (y * y + z * z);
            inertia[1][1] += perVertexMass * (x * x + z * z);
            inertia[2][2] += perVertexMass * (x * x + y * y);
            inertia[0][1] -= perVertexMass * x * y;
            inertia[0][2] -= perVertexMass * x * z;
            inertia[1][2] -= perVertexMass * y * z;
        }
        // Since inertia tensor is symmetric:
        inertia[1][0] = inertia[0][1];
        inertia[2][0] = inertia[0][2];
        inertia[2][1] = inertia[1][2];
    
        setInertiaTensor(inertia);
    }
}