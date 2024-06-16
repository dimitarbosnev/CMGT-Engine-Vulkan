#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP



#pragma once
#include "glm.hpp"
#include "config.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace glm;

namespace cmgt
{
	class WorldSeed;
	class Light;
	class Component;

	class GameObject
	{
	public:
		GameObject(const string& pName);
		id_t getID() { return id; }
		virtual ~GameObject();

		void setName(const string& pName);
		string getName() { return _name; }


		//contains local rotation, scale, position
		void setTransform(const mat4& pTransform);
		const mat4& getTransform() const;

		//access just the local position
		void setLocalPosition(vec3 pPosition);
		void setWorldPosition(vec3 pPosition);
		vec3 getLocalPosition() const;

		//get the objects world position by combining transforms, SLOW use with care
		vec3 getWorldPosition() const;
		mat4 getWorldTransform() const;

		//change LOCAL position, rotation, scaling
		void Translate(vec3 pTranslation);
		void Rotate(float pAngle, vec3 pAxis);
		void Scale(vec3 pScale);


		void addComponent(Component* pBehaviour);
		template<class T>  T* getComponent();
		virtual void update(float pStep);

		//child management, note that add/remove and setParent are closely coupled.
		//a.add(b) has the same effect as b.setParent(a)
		//Adding a gameobject or resetting the parent, recursively passes on the world pointer to all child objects

		//shortcut to set the parent of pChild to ourselves
		void add(GameObject* pChild);
		//shortcut to set the parent of pChild to nullptr
		void remove(GameObject* pChild);

		void setParent(GameObject* pGameObject);
		GameObject* getParent() const;

		int getChildCount() const;
		GameObject* getChildAt(int pIndex) const;

		WorldSeed* getWorld() const;

	protected:

		string _name;
		id_t id;
		mat4 _transform;

		GameObject* _parent;
		vector<GameObject*> _children;

		vector<Component*> _components;
		WorldSeed* _world;

		//update children list administration
		void _innerAdd(GameObject* pChild);
		void _innerRemove(GameObject* pChild);

		//used to pass on pointer to the world to a gameobject
		virtual void _setWorldRecursively(WorldSeed* pWorldSeed);

	private:
		GameObject(const GameObject&) = delete;
		GameObject& operator= (const GameObject&) = delete;
	};
}
#endif // GAMEOBJECT_HPP