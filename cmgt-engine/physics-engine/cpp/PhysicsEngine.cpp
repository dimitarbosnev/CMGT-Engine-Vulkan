
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/Collider.h"
#include <iostream>
namespace cmgt
{

    PhysicsEngine::PhysicsEngine() : Singelton<PhysicsEngine>(this)
    {
    }

    PhysicsEngine::~PhysicsEngine()
    {
    }

    void PhysicsEngine::update(float pStep)
    {

        for(int i = 0; i < colliders.size(); i++)
        for (int j = i + 1; j < colliders.size(); j++) {

            if(colliders[i] != nullptr && colliders[j] != nullptr){
                Shape shape1(colliders[i]), shape2(colliders[j]);
                //if(checkCollision(shape1, shape2)){
                    //std::cout << "COLLISION DETECTED!!!" << std::endl;
                //}
            }
        }
    }

    // GJK Algorithm
    std::vector<glm::vec3> PhysicsEngine::checkCollision(Shape &shape1, Shape &shape2)
    {
        // our simplex that we are looking to build
        std::vector<glm::vec3> simplex(4);
        
    // calculate point 1
        glm::vec3 direction = shape2.worldTransform[3] - shape1.worldTransform[3];
        glm::vec3 supportPoint = getSupportPoint(shape1, shape2, direction);
        //simplex[0] = supportPoint;
        simplex.push_back(supportPoint);
        // Get the direction from first point towards the origin
        direction = -supportPoint;

    // calculate point 2
        glm::vec3 supportPoint2 = getSupportPoint(shape1, shape2, direction);
        // check if the support point passed the origin
        if (glm::dot(supportPoint2, glm::normalize(direction)) < 0)
            return simplex;

        //simplex[1] = supportPoint2;
        simplex.push_back(supportPoint2);

    // calculate point 3
        glm::vec3 pointB = simplex[0]; // First point
        glm::vec3 pointA = simplex[1]; // Second point

        glm::vec3 vecAB = pointB - pointA;
        glm::vec3 vecAO = -pointA;

        glm::vec3 crossABO = glm::cross(vecAB, vecAO);       // normal of plane ABO
        glm::vec3 crossABO_AB = glm::cross(crossABO, vecAB); // normal of line AB in the plane ABO

        direction = crossABO_AB;

        glm::vec3 supportPoint3 = getSupportPoint(shape1, shape2, direction);
        // check if the support point passed the origin
        if (glm::dot(supportPoint3, glm::normalize(direction)) < 0)
            return simplex;

        //simplex[2] = supportPoint3;
        simplex.push_back(supportPoint3);

    // calculate point 4
        glm::vec3 pointC = simplex[2];

        glm::vec3 vecAC = pointC - pointA;

        glm::vec3 crossABC = glm::cross(vecAB, vecAC);

        direction = crossABC * (glm::dot(crossABC, vecAO) > 0 ? 1 : -1);

        glm::vec3 supportPoint4 = getSupportPoint(shape1, shape2, direction);

        // check if the support point passed the origin
        if (glm::dot(supportPoint4, glm::normalize(direction)) < 0)
            return simplex;

        //simplex[3] = supportPoint4;
        simplex.push_back(supportPoint4);

    //Final Checks 

        //return loopCheck(simplex,shape1, shape2);
    }

    glm::vec3 PhysicsEngine::getSupportPoint(Shape &shape1, Shape &shape2, glm::vec3 dir)
    {
        dir = glm::normalize(dir);

        return getFurthestPoint(shape2, -dir) - getFurthestPoint(shape1, dir);
    }

    glm::vec3 PhysicsEngine::getFurthestPoint(Shape &shape, glm::vec3 dir)
    {
        dir = glm::normalize(dir);

        glm::vec3 furthestVert;
        float value;
        for (Vertex vert : shape.colliderMesh)
        {
            float temp = glm::dot(vert.position, dir);
            if (temp > value)
            {
                furthestVert = vert.position;
                value = temp;
            }
        }

        //we transform the point in world space

        return shape.worldTransform[3] * glm::vec4(furthestVert,1);
    }

    bool PhysicsEngine::loopCheck(glm::vec3 simplex[4], Shape &shape1, Shape &shape2)
    {
        //NOTE: Its possible that the normal of ABC has to be recalculated and checked ones we change a point
        glm::vec3 direction;
        while (true)
        {
            glm::vec3 pointB = simplex[0]; // First point
            glm::vec3 pointA = simplex[1]; // Second point
            glm::vec3 pointC = simplex[2]; // Third point
            glm::vec3 pointD = simplex[3]; // Forth point

            glm::vec3 vecAD = pointD - pointA;
            glm::vec3 vecBD = pointD - pointB;
            glm::vec3 vecCD = pointD - pointC;
            glm::vec3 vecDO = -pointD;

            glm::vec3 crossDAB = glm::cross(vecAD, vecBD);
            // if it is outside of plane we start over
            if (glm::dot(crossDAB, vecDO) > 0) {
                direction = crossDAB;

                glm::vec3 supportPoint3 = getSupportPoint(shape1, shape2, direction);
                // check if the support point passed the origin
                if (glm::dot(supportPoint3, glm::normalize(direction)) < 0)
                    return false;

                simplex[2] = supportPoint3;
                continue;
            }

            glm::vec3 crossDCA = glm::cross(vecCD, vecAD);
            // if it is outside of plane we start over
            if (glm::dot(crossDCA, vecDO) > 0) {
                direction = crossDCA;

                glm::vec3 supportPoint2 = getSupportPoint(shape1, shape2, direction);
                // check if the support point passed the origin
                if (glm::dot(supportPoint2, glm::normalize(direction)) < 0)
                    return false;
        
                simplex[1] = supportPoint2;
                continue;
            }

            // This needs a new vector to the origin
            glm::vec3 crossDBC = glm::cross(vecBD, vecCD);
            // if it is outside of plane we start over
            if (glm::dot(crossDBC, vecDO) > 0)
            {
                direction = crossDBC;

                glm::vec3 supportPoint1 = getSupportPoint(shape1, shape2, direction);

                // check if the support point passed the origin
                if (glm::dot(supportPoint1, glm::normalize(direction)) < 0)
                    return false;
        
                simplex[0] = supportPoint1;
                continue;
            }

            return true;
        }
    }

}