#include "ObjectMgr.h"
#include "EntityBase.h"

bool ObjectMgr::registerEntity(EntityBase * obj_)
{
	auto r = _objMap.insert(make_pair(obj_->id(), obj_));
	return r.second;
}

bool ObjectMgr::removeEntity(EntityBase * obj_)
{
	auto r = _objMap.erase(obj_->id());

	delete obj_;
	obj_ = nullptr;

	return r == 1;
}

EntityBase * ObjectMgr::getEntityById(const int id_)
{
	return _objMap.find(id_)->second;
}