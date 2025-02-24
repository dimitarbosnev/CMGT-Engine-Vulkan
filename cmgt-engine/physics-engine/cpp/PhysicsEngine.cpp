
#include "physics-engine/PhysicsEngine.h"
#include "physics-engine/PhysicsBody.h"
#include "physics-engine/Collider.h"
#include "physics-engine/Shape.h"
#include "core/Globals.h"
#include "minimal/log.h"
#include <iostream>

namespace cmgt
{
    PhysicsEngine::PhysicsEngine() : Singelton<PhysicsEngine>(this)
    {
    }

    PhysicsEngine::~PhysicsEngine()
    {
    }

    void PhysicsEngine::phys_tick(float pStep)
    {
       
        auto start = clock::now();
        for(int i = 0; i < colliders.size(); i++){
            for (int j = i + 1; j < colliders.size(); j++) {

                if(colliders[i] != nullptr && colliders[j] != nullptr){
                    Shape shape1(colliders[i]), shape2(colliders[j]);
                    Simplex simplex; 
                    #ifdef SAT
                        CollisionInfo info(shape1,colliders[i],shape2,colliders[j]);                     
                        if(SATcheckCollision(shape1,shape2,&info)){
                            CollisionResponse(info, pStep);
                        }
                    #endif

                    #ifdef GJK
                    if(GJKcheckCollision(shape1, shape2, simplex)){
                        CollisionInfo info(shape1,colliders[i],shape2,colliders[j]);  
                        GetCollisionInfo(shape1,shape2, simplex,&info);
                        CollisionResponse(info, pStep);
                    }
                    #endif
                }
            }
        }
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<us>(end - start);
        max_time = max_time < elapsed? elapsed : max_time;
        min_time = min_time > elapsed? elapsed : min_time;
        sum_time += elapsed;
        counter++;
        if(counter == ticks){
            static us average_time = sum_time / ticks;
            Log::test_complete = true;
            std::stringstream ss;
            ss << "Max time is: " << max_time << " Min time is: " << min_time << " Average time is: " << average_time;
            Log::msg(ss.str());
        }
        //std::cout << "Elapsed time SAT: " << elapsed.count() << " mc\n";
    }

    bool PhysicsEngine::rayCast(const glm::vec3& origin, const glm::vec3& dir, RayInfo* rayInfo) {

        glm::vec3 normDir = glm::normalize(dir);
        std::vector<Collider*>& colliders = PhysicsEngine::get()->colliders;

        for(Collider* collider : colliders){
            if(collider->getOwner() == rayInfo->sender) continue;
            if(collider->rayIntersectCheck(origin,normDir,rayInfo)){
                rayInfo->hit = true;
                rayInfo->hitCollider = collider;
                return true;
            }
        }

        return false;
    }
    void PhysicsEngine::CollisionResponse(CollisionInfo& info, float phys_tick){

        //don't forget to implement for both dynamic and static objects
        glm::vec3 relative1 = info.collider2.first.centroid - info.collider1.first.centroid;
        glm::vec3 relative2 = info.collider1.first.centroid - info.collider2.first.centroid;
        //glm::vec3 resolution = relative * (info.peneterationDepth + EPSILON);
        float mass1 = info.collider1.second->getInverseMass();
        float mass2 = info.collider2.second->getInverseMass();
        float totalMass = mass1 + mass2;
        glm::vec3 resolution1 = info.collisionNormal * (info.peneterationDepth + 0.001f) * (mass1 / totalMass);
        glm::vec3 resolution2 = info.collisionNormal * (info.peneterationDepth +  0.001f) * (mass2 / totalMass);
        if(glm::dot(relative1,resolution1) < 0)
            resolution1 = -resolution1;
        if(glm::dot(relative2,resolution2) > 0)
            resolution2 = -resolution2;
        info.collider1.second->velocity = info.collider1.second->reflectVelosity(info.collisionNormal);
        info.collider2.second->velocity = info.collider2.second->reflectVelosity(info.collisionNormal);

        if(info.collider1.second->getPhysType() == phys_type::DYNAMIC)
            info.collider1.second->getTransform().setWorldPosition((glm::vec3(info.collider1.first.worldTransform[3])-resolution1));
        if(info.collider2.second->getPhysType() == phys_type::DYNAMIC)
            info.collider2.second->getTransform().setWorldPosition((glm::vec3(info.collider2.first.worldTransform[3])+resolution2));
        
        //std::cout << "Contact Point: " <<  info.contactPoint << std::endl;
        //{
        //    //collider1
        //    Collider* collider = info.collider1.second;
        //    if(collider->getPhysType() == phys_type::DYNAMIC){
        //        Shape& shape = info.collider1.first;
        //        glm::vec3 r = relative1 - collider->velocity;
        //
        //        glm::vec3 inertia = glm::cross (collider->getInertiaTensor() * glm::cross (r, info.collisionNormal), r);
        //
        //        glm::vec3 deltaAngularVelocity =  inertia * phys_tick;
        //        collider->angularVelosity += deltaAngularVelocity;
        //    }
        //}
        //
        //{
        //    //collider2
        //    Collider* collider = info.collider2.second;
        //    if(collider->getPhysType() == phys_type::DYNAMIC){
        //        Shape& shape = info.collider2.first;
        //        glm::vec3 r = relative2 - collider->velocity;
        //        
        //        glm::vec3 inertia = glm::cross (collider->getInertiaTensor() * glm::cross (r, info.collisionNormal), r);
        //
        //        glm::vec3 deltaAngularVelocity =  inertia * phys_tick;
        //        collider->angularVelosity += deltaAngularVelocity;
        //    }
        //}
    }



    void PhysicsEngine::GetCollisionInfo(const Shape& shape1, const Shape& shape2, Simplex& simplex, CollisionInfo* info){
        std::vector<glm::vec3> polytope{simplex[0],simplex[1],simplex[2],simplex[3]};
	    std::vector<size_t> faces = {
		    0, 1, 2,
		    0, 3, 1,
		    0, 2, 3,
		    1, 3, 2
	    };

	    // list: vec4(normal, distance), index: min distance
	    auto [normals, minFace] = GetFaceNormals(polytope, faces);

        glm::vec3  minNormal;
	    float minDistance = MAX;
	
	    while (minDistance == MAX) {
		    minNormal   = normals[minFace].xyz();
		    minDistance = normals[minFace].w;
 
		    glm::vec3 support = getSupportPoint(shape1, shape2, minNormal);
		    float sDistance = glm::dot(minNormal, support);
 
		    if (abs(sDistance - minDistance) > -EPSILON) {
			    minDistance = MAX;
            
                std::vector<std::pair<size_t, size_t>> uniqueEdges;

			    for (size_t i = 0; i < normals.size(); i++) {
				    if (glm::dot(normals[i].xyz(), support-polytope[faces[i*3]]) > 0) {
					    size_t f = i * 3;

					    AddIfUniqueEdge(uniqueEdges, faces, f,     f + 1);
					    AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
					    AddIfUniqueEdge(uniqueEdges, faces, f + 2, f    );

					    faces[f + 2] = faces.back(); faces.pop_back();
					    faces[f + 1] = faces.back(); faces.pop_back();
					    faces[f    ] = faces.back(); faces.pop_back();

					    normals[i] = normals.back(); // pop-erase
					    normals.pop_back();

					    i--;
				    }
			    }

                std::vector<size_t> newFaces;
			    for (auto [edgeIndex1, edgeIndex2] : uniqueEdges) {
				    newFaces.push_back(edgeIndex1);
				    newFaces.push_back(edgeIndex2);
				    newFaces.push_back(polytope.size());
			    }
			 
			    polytope.push_back(support);

			    auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);

                if (newNormals.empty()) {
                    //no New normals added exiting loop
                    break;
                }
                float oldMinDistance = MAX;
			    for (size_t i = 0; i < normals.size(); i++) {
				    if (normals[i].w < oldMinDistance) {
					    oldMinDistance = normals[i].w;
					    minFace = i;
				}
			    }
                //why does it crash here? (Read access violation)
		        if (newNormals[newMinFace].w < oldMinDistance) {
				    minFace = newMinFace + normals.size();
			    }
 
			    faces.insert(faces.end(), newFaces.begin(), newFaces.end());
			    normals.insert(normals.end(), newNormals.begin(), newNormals.end());
		    }
        }

 
        info->collisionNormal = glm::normalize(minNormal);
        info->peneterationDepth = minDistance;
    
    }

    std::pair<std::vector<glm::vec4>, size_t> PhysicsEngine::GetFaceNormals(const std::vector<glm::vec3>& polytope, const std::vector<size_t>& faces)
    {
        std::vector<glm::vec4> normals;
        size_t minTriangle = 0;
        float  minDistance = MAX;
    
        for (size_t i = 0; i < faces.size(); i += 3) {
            glm::vec3 a = polytope[faces[i    ]];
            glm::vec3 b = polytope[faces[i + 1]];
            glm::vec3 c = polytope[faces[i + 2]];
    
            glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
            float distance = glm::dot(normal, a);
    
            if (distance < 0) {
                normal   *= -1;
                distance *= -1;
            }
    
            normals.emplace_back(normal, distance);
    
            if (distance < minDistance) {
                minTriangle = i / 3;
                minDistance = distance;
            }
        }
    
        return { normals, minTriangle };
    }

    void PhysicsEngine::AddIfUniqueEdge( std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b)
    {
        auto reverse = std::find(                       //      0--<--3
            edges.begin(),                              //     / \ B /   A: 2-0
            edges.end(),                                //    / A \ /    B: 0-2
            std::make_pair(faces[b], faces[a]) //   1-->--2
        );
     
        if (reverse != edges.end()) {
            edges.erase(reverse);
        }
     
        else {
            edges.emplace_back(faces[a], faces[b]);
        }
    }

    // GJK Algorithm
    bool PhysicsEngine::GJKcheckCollision(const Shape &shape1, const Shape &shape2, Simplex& simplex)
    {
        
    // calculate point 1
        glm::vec3 direction = shape2.centroid - shape1.centroid;
        glm::vec3 supportPoint = getSupportPoint(shape1, shape2, direction);
        simplex[0] = supportPoint;

        // Get the direction from first point towards the origin
        //direction = -direction;
        direction = -supportPoint;

    // calculate point 2
        glm::vec3 supportPoint2 = getSupportPoint(shape1, shape2, direction);
        // check if the support point passed the origin
        if (glm::dot(supportPoint2, glm::normalize(direction)) < 0)
            return false;
        
        simplex[1] = supportPoint2;

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
            return false;

        simplex[2] = supportPoint3;

    // calculate point 4
        glm::vec3 pointC = simplex[2];

        glm::vec3 vecAC = pointC - pointA;

        glm::vec3 crossABC = glm::cross(vecAB, vecAC);

        direction = crossABC * (glm::dot(crossABC, vecAO) > 0 ? 1.f : -1.f);

        glm::vec3 supportPoint4 = getSupportPoint(shape1, shape2, direction);

        // check if the support point passed the origin

        if (glm::dot(supportPoint4, glm::normalize(direction)) < 0)
            return false;

        simplex[3] = supportPoint4;

    //Final Checks 

        return loopCheck(simplex,shape1, shape2);
    }






    glm::vec3 PhysicsEngine::getSupportPoint(const Shape &shape1, const Shape &shape2, glm::vec3 dir)
    {
        dir = glm::normalize(dir);

        return shape1.getFurthestPoint(dir) - shape2.getFurthestPoint(-dir);
    }





    
    bool PhysicsEngine::loopCheck(Simplex& simplex,const Shape &shape1,const Shape &shape2)
    {
        //NOTE: Its possible that the normal of ABC has to be recalculated and checked ones we change a point
        glm::vec3 direction;
        int count = -1;
        int max = 100;
        begin:

            count++;
            glm::vec3 pointA = simplex[0]; // First point
            glm::vec3 pointB = simplex[1]; // Second point
            glm::vec3 pointC = simplex[2]; // Third point
            glm::vec3 pointD = simplex[3]; // Newest point

            glm::vec3 vecDA = pointA - pointD;
            glm::vec3 vecDB = pointB - pointD;
            glm::vec3 vecDC = pointC - pointD;
            glm::vec3 vecDO = -pointD;

            glm::vec3 crossDAB = glm::cross(vecDA, vecDB);
            // if it is outside of plane we start over
            if (glm::dot(crossDAB, vecDO) > 0) {
                direction = crossDAB;
                
                //std::cout<<"DAB check failed"<<std::endl;
                glm::vec3 supportPoint3 = getSupportPoint(shape1, shape2, direction);
                // check if the support point passed the origin
                if (simplex.inSimplex(supportPoint3) || glm::dot(supportPoint3, glm::normalize(direction)) < 0 || count > max)
                    return false;

                simplex[2] =  simplex[3];
                simplex[3] = supportPoint3;
                goto begin;
            }

            glm::vec3 crossDCA = glm::cross(vecDC, vecDA);
            // if it is outside of plane we start over
            if (glm::dot(crossDCA, vecDO) > 0) {
                direction = crossDCA;
                //std::cout<<"DCA check failed"<<std::endl;
                glm::vec3 supportPoint2 = getSupportPoint(shape1, shape2, direction);
                // check if the support point passed the origin
                if (simplex.inSimplex(supportPoint2) || glm::dot(supportPoint2, glm::normalize(direction)) < 0 || count > max)
                    return false;
                
                simplex[1] = simplex[2];
                simplex[2] = simplex[3];
                simplex[3] = supportPoint2;
                goto begin;
            }

            glm::vec3 crossDBC = glm::cross(vecDB, vecDC);
            // if it is outside of plane we start over
            if (glm::dot(crossDBC, vecDO) > 0)
            {
                direction = crossDBC;
                //std::cout<<"DBC check failed"<<std::endl;
                glm::vec3 supportPoint1 = getSupportPoint(shape1, shape2, direction);

                // check if the support point passed the origin
                if (simplex.inSimplex(supportPoint1) || glm::dot(supportPoint1, glm::normalize(direction)) < -EPSILON || count > max)
                    return false;
        
                simplex[0] = simplex[1];
                simplex[1] = simplex[2];
                simplex[2] = simplex[3];
                simplex[3] = supportPoint1;
                goto begin;
            }

        return true;
    }

    bool PhysicsEngine::SATcheckCollision(const Shape& shape1, const Shape& shape2, CollisionInfo* info){

        info->peneterationDepth = MAX;
        //Check axies
        glm::vec3 axis1 = glm::normalize(shape1.worldTransform[0].xyz()); //shape 1 X-axis
        if(!computeAxis(shape1,shape2,axis1,info)){
            return false;
        }

        glm::vec3 axis2 = glm::normalize(shape1.worldTransform[1].xyz()); //shape 1 Y-axis
        if(!computeAxis(shape1,shape2,axis2,info)){
            return false;
        }
        glm::vec3 axis3 = glm::normalize(shape1.worldTransform[2].xyz()); //shape 1 Z-axis
        if(!computeAxis(shape1,shape2,axis3,info)){
            return false;
        }

        glm::vec3 axis4 = glm::normalize(shape2.worldTransform[0].xyz()); //shape 2 X-axis
        if(!computeAxis(shape1,shape2,axis4,info)){
            return false;
        }

        glm::vec3 axis5 = glm::normalize(shape2.worldTransform[1].xyz()); //shape 2 Y-axis
        if(!computeAxis(shape1,shape2,axis5,info)){
            return false;
        }

        glm::vec3 axis6 = glm::normalize(shape2.worldTransform[2].xyz()); //shape 2 Z-axis
        if(!computeAxis(shape1,shape2,axis6,info)){
            return false;
        }

        glm::vec3 axis7 = glm::normalize(glm::cross(shape1.worldTransform[0].xyz(),shape2.worldTransform[0].xyz())); //shape 1 X-axis cross shape 2 X-axis
        if(glm::length(axis7) >= 1 &&!computeAxis(shape1,shape2,axis7,info)){
            return false;
        }

        glm::vec3 axis8 = glm::normalize(glm::cross(shape1.worldTransform[0].xyz(),shape2.worldTransform[1].xyz())); //shape 1 X-axis cross shape 2 Y-axis
        if(glm::length(axis8) >= 1 && !computeAxis(shape1,shape2,axis8,info) ){
            return false;
        }

        glm::vec3 axis9 = glm::normalize(glm::cross(shape1.worldTransform[0].xyz(),shape2.worldTransform[2].xyz())); //shape 1 X-axis cross shape 2 Z-axis
        if(glm::length(axis9) >= 1 && !computeAxis(shape1,shape2,axis9,info)){
            return false;
        }

        glm::vec3 axis10 = glm::normalize(glm::cross(shape1.worldTransform[1].xyz(),shape2.worldTransform[0].xyz())); //shape 1 Y-axis cross shape 2 X-axis
        if(glm::length(axis10) >= 1 && !computeAxis(shape1,shape2,axis10,info)){
            return false;
        }

        glm::vec3 axis11 = glm::normalize(glm::cross(shape1.worldTransform[1].xyz(),shape2.worldTransform[1].xyz())); //shape 1 Y-axis cross shape 2 Y-axis
        if(glm::length(axis11) >= 1 && !computeAxis(shape1,shape2,axis11,info)){
            return false;
        }
        glm::vec3 axis12 = glm::normalize(glm::cross(shape1.worldTransform[1].xyz(),shape2.worldTransform[2].xyz())); //shape 1 Y-axis cross shape 2 Z-axis
        if(glm::length(axis12) >= 1 && !computeAxis(shape1,shape2,axis12,info)){
            return false;
        }

        glm::vec3 axis13 = glm::normalize(glm::cross(shape1.worldTransform[2].xyz(),shape2.worldTransform[0].xyz())); //shape 1 Z-axis cross shape 2 X-axis
        if(glm::length(axis13) >= 1 && !computeAxis(shape1,shape2,axis13,info)){
            return false;
        }

        glm::vec3 axis14 = glm::normalize(glm::cross(shape1.worldTransform[2].xyz(),shape2.worldTransform[1].xyz())); //shape 1 Z-axis cross shape 2 Y-axis
        if(glm::length(axis14) >= 1 && !computeAxis(shape1,shape2,axis14,info)){
            return false;
        }

        glm::vec3 axis15 = glm::normalize(glm::cross(shape1.worldTransform[2].xyz(),shape2.worldTransform[2].xyz())); //shape 1 Z-axis cross shape 2 Z-axis
        if(glm::length(axis15) >= 1 && !computeAxis(shape1,shape2,axis15,info)){
            return false;
        }

        return true;
    }

    bool PhysicsEngine::computeAxis(const Shape& shape1,const Shape& shape2, glm::vec3 axis, CollisionInfo* info){
        auto [shape1_min, shape1_max] = shape1.getMinMaxValues(axis);
        auto [shape2_min, shape2_max] = shape2.getMinMaxValues(axis);
        //If shapes overlap on aixs return true
        float newPenetration = 0;
        if (shape1_max < shape2_min || shape2_max < shape1_min) {
            return false;
        }

        // The overlapping (penetration) length is the difference between the lower of the two max values
        // and the higher of the two min values.
        float min_of_max = std::min(shape1_max, shape2_max);
        float max_of_min = std::max(shape1_min, shape2_min);
        newPenetration = min_of_max - max_of_min;

        if(newPenetration < info->peneterationDepth){
            info->peneterationDepth = newPenetration;
            info->collisionNormal = axis;
            //info->contactPoint = (((min_of_max + max_of_min) * 0.5f) * axis) + center;
        }
        return true;
    }

}