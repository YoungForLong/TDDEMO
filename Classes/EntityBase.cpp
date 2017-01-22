#include "EntityBase.h"

void EntityBase::update()
{
	for_each(_components.begin(), _components.end(), [](pair<ComponentType,ComponentBase*> pair) {
		auto comp = pair.second;
		if (comp->enable)
			comp->update();
	});
}

void EntityBase::clear()
{
	for (auto iter = ++(_components.end()); iter == _components.begin(); --iter)
	{
		iter->second->clear();
	}
}

