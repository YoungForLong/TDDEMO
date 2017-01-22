#ifndef _ENTITY_BASE_H_
#define _ENTITY_BASE_H_

#include "ObjectBase.h"
#include "ComponentBase.h"
#include "CommonEnum.h"
#include <map>
#include "ObjectMgr.h"

class EntityBase:public ObjectBase
{
public:
	EntityBase(int id_) :ObjectBase(id_) {}

#pragma region Componets
protected:
	map<ComponentType, ComponentBase*> _components;
public:
	template <class T>
	T* getComponent(ComponentType type_);

	template <class T>
	T* addComponent(ComponentType type_);
#pragma endregion

public:
	void update() override;

	void clear() override;

	template<class T>
	static T* create();
};

#endif // !_ENTITY_BASE_H_

template<class T>
inline T * EntityBase::getComponent(ComponentType type_)
{
	return static_cast<T*>(_components[type_]);
}

template<class T>
inline T* EntityBase::addComponent(ComponentType type_)
{
	auto comp = new T;
	comp->init();
	comp->root = this;

	_components.emplace(type_, comp);

	return comp;
}

template<class T>
inline T * EntityBase::create()
{
	auto id_ = OMGR->getNewId();
	auto ret = new T(id_);
	OMGR->registerEntity(ret);
	return ret;
}
