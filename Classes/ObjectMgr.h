#ifndef _OBJECT_MGR_H_
#define _OBJECT_MGR_H_
#include "Singleton.h"
#include <map>

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
};

#define OMGR ObjectMgr::instance()

#endif

