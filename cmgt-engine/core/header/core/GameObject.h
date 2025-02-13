#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include "core/Object.h"
#include "core/Transform.h"
#include <string>
#include <vector>

namespace cmgt
{
	class World;
	class Component;
	class Mesh;
	class GameObject : public Object
	{
	public:
		GameObject(const  std::string& pName);

		virtual ~GameObject();

		//contains local rotation, scale, position
		void setTransform(Transform& pTransform);
		Transform& getTransform();

		//access just the local position

		void addComponent(Component* pBehaviour);

		template<typename T> T* getComponent() {
			for(Component* child : _components)
			{
				if(T* component = dynamic_cast<T*>(child)){
					return component;
				}
			}
			return nullptr;
		}

		void update(float pStep) override;
		void render(const VulkanFrameData& frameData) override;
		void physics_update(float phys_step) override;
		//child management, note that add/remove and setParent are closely coupled.
		//a.add(b) has the same effect as b.setParent(a)
		//Adding a gameobject or resetting the parent, recursively passes on the world pointer to all child objects

		//shortcut to set the parent of pChild to ourselves
		void add(GameObject* pChild);
		//shortcut to set the parent of pChild to nullptr
		void remove(GameObject* pChild);

		void setParent(GameObject* pGameObject);
		GameObject* getParent();

		int getChildCount() const;
		GameObject* getChildAt(int pIndex) const;

		World* getWorld() const;

	protected:
		//Used to spawn objects from world seed
		Transform _transform;

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