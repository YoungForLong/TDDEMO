#ifndef _OBJECT_MGR_H_
#define _OBJECT_MGR_H_
#include "Singleton.h"
#include <map>
#include "cocos2d\cocos\math\Vec2.h"

using namespace std;

class EntityBase;

//�ڴ������������ǵ�ͼ�ϵ����������CSP
class ObjectMgr :public Singleton<ObjectMgr>
{
private:
	map<int, EntityBase*> _objMap;

	//��100�Ժ����Զ������ID
	int _curID = 100;
public:
	bool registerEntity(EntityBase* obj_);
	bool removeEntity(EntityBase* obj_);
	EntityBase* getEntityById(const int id_);

	//��������ʵ�壬���ǲ�����ɾ���ʹ�����ɾ���ʹ������ӳٵ���һ֡
	void updateAll();

	int getNewId();

	cocos2d::Vec2 pos_of_camera;
};

#define OMGR ObjectMgr::instance()

#endif

