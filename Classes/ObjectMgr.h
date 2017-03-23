#ifndef _OBJECT_MGR_H_
#define _OBJECT_MGR_H_
#include "Singleton.h"
#include <map>
#include "cocos2d\cocos\math\Vec2.h"

using namespace std;

class EntityBase;

//内存管理区，如果是地图上的物体请访问CSP
class ObjectMgr :public Singleton<ObjectMgr>
{
private:
	map<int, EntityBase*> _objMap;

	//从100以后是自动分配的ID
	int _curID = 100;
public:
	bool registerEntity(EntityBase* obj_);
	bool removeEntity(EntityBase* obj_);
	EntityBase* getEntityById(const int id_);

	//更新所有实体，但是不允许删除和创建，删除和创建将延迟到下一帧
	void updateAll();

	int getNewId();

	cocos2d::Vec2 pos_of_camera;
};

#define OMGR ObjectMgr::instance()

#endif

