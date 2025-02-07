#ifndef COLLIDER_H
#define COLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "core/Component.h"
#include "minimal/types.h"
#include "core/Mesh.h"
#include <list>
namespace cmgt
{
	class Collider : public Component
	{
	protected:
		glm::vec3 offset;
		glm::vec3 scale;
	public:
		Collider(std::vector<Vertex> meshData);
		//behaviour should be able to update itself every step and MUST be implemented
		virtual void update(float pStep) override;
		std::vector<Vertex> colliderMesh;
	private:

		//disallow copy and assignment
		Collider(const Collider&);
		Collider& operator=(const Collider&);
	};

	struct Shape{
		Shape(Collider* collider) : colliderMesh(collider->colliderMesh){
			worldTransform = collider->getTransform().getWorldTransform();
		}
		const std::vector<Vertex>& colliderMesh;
		glm::mat4 worldTransform;
	};
} 
#endif // COLLIDER_H