#ifndef MESHCOLLIDER_H
#define MESHCOLLIDER_H

#pragma once
#include "minimal/glm.h"
#include "physics-engine/Collider.h"

namespace cmgt
{
	class MeshCollider : public Collider
	{
	public:
		MeshCollider(std::vector<Vertex> meshData);
		MeshCollider();
		//behaviour should be able to update itself every step and MUST be implemented
	protected:
		virtual void OnSetOwner() override;
	private:
		void populateCollider(const std::vector<Vertex>& meshData);
		//disallow copy and assignment
		MeshCollider(const MeshCollider&);
		MeshCollider& operator=(const MeshCollider&);
	};
} 
#endif // MESHCOLLIDER_H