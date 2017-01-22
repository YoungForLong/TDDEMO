#ifndef _COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_

#include"CommonEnum.h"

class EntityBase;

class ComponentBase
{
public://properties
	bool enable;
	
	EntityBase* root;//owner

	ComponentType type;
public://logics

	virtual bool init() = 0;

	virtual void update() = 0;

	virtual void clear() = 0;

	template <class T>
	T* create(EntityBase* owner)
	{
		auto ret = new T;
		ret->T::init();
		ret->root = owner;
		return ret;
	}
};



#endif