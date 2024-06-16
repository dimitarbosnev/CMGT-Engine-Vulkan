#ifndef FREEMOVEMENT_HPP
#define FREEMOVEMENT_HPP
#include "glm.hpp"
#include "Component.hpp"
using namespace glm;
namespace cmgt
{
	class GameObject;

	class FreeMovment : public Component
	{
	public:
		FreeMovment();
		//behaviour should be able to update itself every step and MUST be implemented
		void update(float pStep) override;
	protected:

		GameObject* _owner;

	private:

		//disallow copy and assignment
		FreeMovment(const FreeMovment&);
		FreeMovment& operator=(const FreeMovment&);
	};
} 
#endif // FREEMOVEMENT_HPP