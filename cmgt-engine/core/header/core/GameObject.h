#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include <string>
#include <vector>

namespace cmgt
{
	class World;
	class Component;

	class GameObject
	{
	public:
		GameObject(const  std::string& pName);
		id_t getID() { return id; }
		virtual ~GameObject();

		void setName(const std::string& pName);
		 std::string getName() { return _name; }


		//contains local rotation, scale, position
		void setTransform(const glm::mat4& pTransform);
		const glm::mat4& getTransform() const;

		//access just the local position
		void setLocalPosition(glm::vec3 pPosition);
		void setWorldPosition(glm::vec3 pPosition);
		glm::vec3 getLocalPosition() const;
		glm::vec3 getScale() const;
		glm::vec3 getEulerRotation() const;
		//get the objects world position by combining transforms, SLOW use with care
		glm::vec3 getWorldPosition() const;
		glm::mat4 getWorldTransform() const;

		//change LOCAL position, rotation, scaling
		void Translate(glm::vec3 pTranslation);
		void Rotate(float pAngle, glm::vec3 pAxis);
		void Scale(glm::vec3 pScale);


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

		World* getWorld() const;

	protected:
		//Used to spawn objects from world seed

		 std::string _name;
		id_t id;
		glm::mat4 _transform;

		GameObject* _parent;
		std::vector<GameObject*> _children;

		std::vector<Component*> _components;
		World* _world;

		//update children list administration
		void _innerAdd(GameObject* pChild);
		void _innerRemove(GameObject* pChild);

		//used to pass on pointer to the world to a gameobject
		virtual void _setWorldRecursively(World* pWorldSeed);

	private:
		GameObject(const GameObject&);
		GameObject& operator= (const GameObject&);
	};
}
#endif // GAMEOBJECT_H