#ifndef _ENTITY_BASE_H_
#define _ENTITY_BASE_H_

#include "ObjectBase.h"
#include "ComponentBase.h"
#include "CommonEnum.h"
#include <map>

class EntityBase:public ObjectBase
{
#pragma region Componets
protected:
	map<ComponentType, ComponentBase*> _components;
public:
	template <class T>
	T* getComponent(ComponentType type);

	template <class T>
	void addComponent();
#pragma endregion

public:
	void update()override;

	void clear()override;
};

#endif // !_ENTITY_BASE_H_

template<class T>
inline T * EntityBase::getComponent(ComponentType type)
{
	return static_cast<T*>(_components[type]);
}

template<class T>
inline void EntityBase::addComponent()
{
	auto comp = static_cast<ComponentBase*>(new Type);
	comp->init();
	comp->root = this;
}
