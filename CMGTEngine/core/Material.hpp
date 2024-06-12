#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#pragma once
#include "glm.hpp"

using namespace glm;
using namespace std;

namespace cmgt {
	class GameObject;
	class Mesh;
	class World;

	class Material
	{
	public:
		Material();
		virtual ~Material();
		void setShineColor(vec3 color) {
			this->_shininess = vec4(color, _shininess.w);
		};
		void setShineColor(float r, float g, float b) {
			this->setShineColor(vec3(r, g, b));
		};
		void setShinines(float shininess) {
			this->_shininess.w = shininess;
		};
		/**
		 * Render the given mesh in the given world using the given mvp matrices. Implement in subclass.
		 */
		virtual void render(World* pWorld, Mesh* pMesh, const mat4& pModelMatrix, const mat4& pViewMatrix, const mat4& pPerspectiveMatrix) = 0;
	protected:
		vec4 _shininess = vec4(1);
	};
}
#endif // MATERIAL_HPP
