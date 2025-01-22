
#include "core/GameObject.h"
#include "core/Component.h"
#include "core/ObjectManager.h"
namespace cmgt {

    GameObject::GameObject(const string& pName) : id{ ObjectManager::assignGameObjectID() }, _name{ pName },
        _parent{ nullptr }, _transform{ glm::mat4(1) }, _world{ nullptr } {
        ObjectManager::addGameObject(*this);

    }
    GameObject::~GameObject()
    {
        //detach all children
        _children.clear();

        while (!_components.empty()) {
            delete _components[0];
            _components.erase(_components.begin());
        }
        _components.clear();
        //do not forget to delete behaviour, material, mesh, collider manually if required!
    }

    void GameObject::setName(const string& pName)
    {
        _name = pName;
    }

    void GameObject::setTransform(const glm::mat4& pTransform)
    {
        _transform = pTransform;
    }

    const glm::mat4& GameObject::getTransform() const
    {
        return _transform;
    }

    void GameObject::setLocalPosition(glm::vec3 pPosition)
    {
        _transform[3] = glm::vec4(pPosition, 1);
    }

    void GameObject::setWorldPosition(glm::vec3 pPosition)
    {

        _transform[3] = glm::vec4(pPosition, 1);
    }

    glm::vec3 GameObject::getLocalPosition() const
    {
        return glm::vec3(_transform[3]);
    }

    glm::vec3 GameObject::getScale() const
    {
        return glm::vec3();
    }

    glm::vec3 GameObject::getEulerRotation() const
    {
        glm::vec3 eulerAngles;
        glm::extractEulerAngleXYZ(_transform, eulerAngles.x, eulerAngles.y, eulerAngles.z);
        return eulerAngles;
    }


    void GameObject::addComponent(Component* pBehaviour)
    {
        _components.push_back(pBehaviour);

        pBehaviour->setOwner(this);
    }

    template<class T> T* GameObject::getComponent()
    {
        static_assert(is_base_of<Component, T>::value, "type parameter of this class must derive from Component");
        const auto findType = [](const Component* a) {
            return typeid(T) == typeid(a);
            };
        T* component = static_cast<T*>(*find(_components.begin(), _components.end(), findType));

        return component;
    }
    void GameObject::setParent(GameObject* pParent) {
        //remove from previous parent
        if (_parent != nullptr) {
            _parent->_innerRemove(this);
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
        if (_parent == nullptr) {
            _setWorldRecursively(nullptr);
        }
        else {
            //might still not be available if our parent is not part of the world
            _setWorldRecursively(_parent->_world);
        }
    }

    void GameObject::_innerRemove(GameObject* pChild) {
        for (auto i = _children.begin(); i != _children.end(); ++i) {
            if (*i == pChild) {
                _children.erase(i);
                pChild->_parent = nullptr;
                return;
            }
        }
    }

    void GameObject::_innerAdd(GameObject* pChild)
    {
        _children.push_back(pChild);
        pChild->_parent = this;
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

    GameObject* GameObject::getParent() const {
        return _parent;
    }
    ////////////

    //costly operation, use with care
    glm::vec3 GameObject::getWorldPosition() const
    {
        return glm::vec3(getWorldTransform()[3]);
    }

    //costly operation, use with care
    glm::mat4 GameObject::getWorldTransform() const
    {
        if (_parent == nullptr) return _transform;
        else return _parent->getWorldTransform() * _transform;
    }

    ////////////

    void GameObject::Translate(glm::vec3 pTranslation) {
        setTransform(glm::translate(_transform, pTranslation));
    }

    void GameObject::Scale(glm::vec3 pScale) {
        setTransform(glm::scale(_transform, pScale));
    }

    void GameObject::Rotate(float pAngle, glm::vec3 pAxis) {
        setTransform(glm::rotate(_transform, pAngle, pAxis));
    }

    void GameObject::update(float pStep)
    {
        //make sure behaviour is updated after worldtransform is set
        for (Component* component : _components)
            component->update(pStep);

        for (GameObject* child : _children) {
            child->update(pStep);
        }
    }

    void GameObject::_setWorldRecursively(WorldSeed* pWorld) {
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

    WorldSeed* GameObject::getWorld() const {
        return _world;
    }
}