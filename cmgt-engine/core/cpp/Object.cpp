
#include "core/Object.h"
#include "core/ObjectManager.h"
namespace cmgt {

    Object::Object() {
        ObjectManager::get()->addObject(this);
    }
    Object::~Object()
    {
        //do not forget to delete behaviour, material, mesh, collider manually if required!
    }

    void Object::setName(const  std::string& pName)
    {
        _name = pName;
    }
}