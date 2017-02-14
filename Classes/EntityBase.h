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
	//更新所有组件,子类显式调用，在开头
	virtual void update() override
	{
		for_each(_components.begin(), _components.end(), [](pair<ComponentType, ComponentBase*> pair) {
			auto comp = pair.second;
			if (comp->enable)
				comp->update();
		});
	}

	//清除组件，子类显式调用，在结尾处
	virtual void clear() override
	{
		auto iter = --_components.end();
		while (iter != --_components.begin())
		{
			iter->second->clear();
			delete (iter->second);
			--iter;
		}
	}

	//初始化信息
	virtual bool init() { return true; }

	template<class T>
	static T* create();
};


template<class T>
inline T * EntityBase::getComponent(ComponentType type_)
{
	return static_cast<T*>(_components[type_]);
}

template<class T>
inline T* EntityBase::addComponent(ComponentType type_)
{
	auto comp = new T;
	comp->root = this;
	comp->init();

	_components.emplace(type_, comp);

	return comp;
}

template<class T>
inline T * EntityBase::create()
{
	auto id_ = OMGR->getNewId();
	auto ret = new T(id_);
	if (ret->init())
	{
		OMGR->registerEntity(ret);
		return ret;
	}
	else
		return nullptr;
}


#endif // !_ENTITY_BASE_H_