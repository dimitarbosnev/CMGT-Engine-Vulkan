#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include <utility>
#include <tuple>
#include <vector>
#include <list>

namespace cmgt
{
	class Collider;
	class PhysicsBody;
	struct Shape;

	struct CollisionInfo {
		CollisionInfo(Shape& rShape1, Collider* pCollider1, Shape& rShape2, Collider* pCollider2) : 
		collider1(rShape1,pCollider1), collider2(rShape2,pCollider2){

		}
		glm::vec3 collisionNormal = glm::vec3(0);
		float peneterationDepth = 0;
		bool hasCollision = true;
		std::pair<Shape&,Collider*> collider1;
		std::pair<Shape&,Collider*> collider2;
	};

	struct Simplex{
		glm::vec3 vertecies[4]{};

		bool inSimplex(glm::vec3 point){
			//If the point is contained in the simplex return true to exit the loop
			if(vertecies[0] == point || vertecies[1] == point || vertecies[3] == point || vertecies[4] == point)
				return true;
	
			return false;
		}
		
		glm::vec3& operator[] (int i){
			return vertecies[i];
		}
	};

	//struct Face{
	//	size_t indecies[3];
	//	size_t& operator[] (size_t i){
	//		return indecies[i];
	//	}
	//};

	class PhysicsEngine : public Singelton<PhysicsEngine> {
		friend class PhysicsBody;
	public:
		PhysicsEngine();
		~PhysicsEngine();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep); 
		const glm::vec3& getGravity() { return gravity; }
		void addCollider(Collider* collider){colliders.push_back(collider);}
		
		private:
		glm::vec3 gravity;
		//The functions responsible for collision detection
		static void CollisionResponse(CollisionInfo& info); 
		// EPA algorithm
		static void GetCollisionInfo(const Shape& shape1, const Shape& shape2, Simplex& simplex, CollisionInfo* info);
		static std::pair<std::vector<glm::vec4>, size_t> GetFaceNormals(const std::vector<glm::vec3>& polytope, const std::vector<size_t>& faces);
		static void AddIfUniqueEdge( std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a,size_t b);
		//
		// GJK Algorithm
		static bool GJKcheckCollision(const Shape& shape1, const Shape& shape2, Simplex& simplex);
		static glm::vec3 getSupportPoint(const Shape& shape1, const Shape& shape2, glm::vec3 dir);
		static bool loopCheck(Simplex& simplex, const Shape& shape1, const Shape& shape2);
		//
		//SAT Algorithm
		static bool SATcheckCollision(const Shape& shape1, const Shape& shape2, CollisionInfo* info);
		static bool computeAxis(const Shape& shape1,const Shape& shape2, glm::vec3 axis, CollisionInfo* info);
		static bool checkAxisOverlap(float min1, float max1, float min2, float max2, glm::vec3 axis, CollisionInfo* info);
		//
		//disallow copy and assignment
		PhysicsEngine(const PhysicsEngine&);
		PhysicsEngine& operator=(const PhysicsEngine&);
		std::vector<PhysicsBody*> physicsBodies = {};
		std::vector<Collider*> colliders = {};
	};
} 
#endif // PHYSICSENGINE_H