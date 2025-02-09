
#include "core/GameObject.h"
#include "core/Component.h"
namespace cmgt {

    GameObject::GameObject(const  std::string& pName) : _world{ nullptr } {
            _name = pName;
    }
    GameObject::~GameObject()
    {
        _children.clear();
        _components.clear();
    }

    void GameObject::setTransform(Transform& pTransform)
    {
        _transform.setParent(pTransform.getParent());
    }

    Transform& GameObject::getTransform()
    {
        return _transform;
    }

    void GameObject::addComponent(Component* pBehaviour)
    {
        _components.push_back(pBehaviour);

        pBehaviour->setOwner(this);
        pBehaviour->OnSetOwner();
    }


    void GameObject::setParent(GameObject* pParent) {
        //remove from previous parent
        if (_transform.getParent() != nullptr) {
            _transform.getParent()->_innerRemove(this);
        }

        //set new parent
        if (pParent != nullptr) {
            pParent->_innerAdd(this);
        }

        //if we have been detached from our parent, make sure
        //the world reference for us and all our children is set to null
        //if we have been attached to a parent, make sure
        //the world reference for us and all our children is set to our parent world reference
        //(this could still be null if the parent or parent's parent is not attached to the world)
        if (_transform.getParent() == nullptr) {
            _setWorldRecursively(nullptr);
        }
        else {
            //might still not be available if our parent is not part of the world
            _setWorldRecursively(_transform.getParent()->_world);
        }
    }

    void GameObject::_innerRemove(GameObject* pChild) {
        for (auto i = _children.begin(); i != _children.end(); ++i) {
            if (*i == pChild) {
                _children.erase(i);
                pChild->_transform.setParent(nullptr);
                return;
            }
        }
    }

    void GameObject::_innerAdd(GameObject* pChild)
    {
        _children.push_back(pChild);
        pChild->_transform.setParent(this);
    }

    void GameObject::add(GameObject* pChild) {
        pChild->setParent(this);
    }

    void GameObject::remove(GameObject* pChild) {
        pChild->setParent(nullptr);
        for (int i = 0; i < _children.size(); i++)
            if (_children[i] == pChild) {
                this->_children.erase(_children.begin() + i);
                break;
            }

    }

    GameObject* GameObject::getParent() {
        return _transform.getParent();
    }
    ////////////

    //costly operation, use with care
    void GameObject::update(float pStep)
    {
        //make sure behaviour is updated after worldtransform is set
        for (Component* component : _components)
            component->update(pStep);

        for (GameObject* child : _children) {
            child->update(pStep);
        }
    }

    void GameObject::_setWorldRecursively(World* pWorld) {
        _world = pWorld;

        for (int i = _children.size() - 1; i >= 0; --i) {
            _children[i]->_setWorldRecursively(pWorld);
        }
    }

    int GameObject::getChildCount() const {
        return _children.size();
    }

    GameObject* GameObject::getChildAt(int pIndex) const {
        return _children[pIndex];
    }

    World* GameObject::getWorld() const {
        return _world;
    }
}