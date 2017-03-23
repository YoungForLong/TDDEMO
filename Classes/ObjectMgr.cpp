#include "ObjectMgr.h"
#include "EntityBase.h"
#include "CompMoving.h"


bool ObjectMgr::registerEntity(EntityBase * obj_)
{
	auto r = _objMap.insert(make_pair(obj_->id(), obj_));
	return r.second;
}

bool ObjectMgr::removeEntity(EntityBase * obj_)
{
	auto r = _objMap.erase(obj_->id());

	obj_->clear();

	delete obj_;
	obj_ = nullptr;

	return r == 1;
}

EntityBase * ObjectMgr::getEntityById(const int id_)
{
	return _objMap.find(id_)->second;
}

void ObjectMgr::updateAll()
{
	auto hero = getEntityById(hero_id);
	if (hero)
	{
		pos_of_camera = hero->getComponent<CompMoving>(comp_moving)->position();
	}

	for (auto iter = _objMap.begin(); iter != _objMap.end(); ++iter)
	{
		auto entity = (*iter).second;
		entity->update();
	}
}

int ObjectMgr::getNewId()
{
	return _curID++;
}
