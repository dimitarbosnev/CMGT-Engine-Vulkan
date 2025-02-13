#ifndef OBJECT_H
#define OBJECT_H
/*
* Base class for all CMGT-Engine classes : Except Managers
*
*
*/


#pragma once
#include "minimal/glm.h"
#include "minimal/types.h"
#include "vulkan-api/VulkanFrameData.h"
#include <string>
#include <vector>

namespace cmgt
{
	class World;
	class Component;

	class Object
	{
		friend class ObjectManager;
	public:
		Object();
		//Object should only be deleted through the ObjectManager
		virtual ~Object();
		const id_t getID() { return _id; }
		void setName(const std::string& pName);
		std::string getName() { return _name; }
		virtual void update(float pStep);
		virtual void render(const VulkanFrameData& frameData);
		virtual void physics_update(float phys_step);
	protected:
		std::string _name;
		//The ID system can be improved
		id_t _id;
	private:
		void Serialize();
		void Deserialize();
	};
}
#endif // OBJECT_H