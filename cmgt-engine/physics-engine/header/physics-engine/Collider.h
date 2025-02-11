#ifndef COLLIDER_H
#define COLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"
#include "minimal/types.h"
#include "core/Mesh.h"
#include "physics-engine/PhysicsBody.h"
#include <list>
namespace cmgt
{
	struct Face{
		glm::vec3 vertecies[3];
		const glm::vec3& a(){ return vertecies[0];}
		const glm::vec3& b(){ return vertecies[1];}
		const glm::vec3& c(){ return vertecies[2];}

		const glm::vec3& operator[] (int i){
			return vertecies[i];
		}
	};

	struct Shape;
	class Collider : public Component
	{
	protected:
		glm::vec3 offset;
		glm::vec3 scale;
	public:
		Collider();
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep) override;
		std::list<glm::vec3> colliderMesh;
		//used in the SAT algorithm
		virtual std::pair<float, float> getMinMaxValues(const Shape& shape, glm::vec3 axis);
		//used in the GJK/EPA algorithm
		virtual glm::vec3 getFurthestPoint(const Shape& shape1,glm::vec3 dir);
		PhysicsBody& getPhysicsBody(){return *physicsBody;}
	private:
		PhysicsBody* physicsBody;
		//disallow copy and assignment
		Collider(const Collider&);
		Collider& operator=(const Collider&);
	};
} 
#endif // COLLIDER_H