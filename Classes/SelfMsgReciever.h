#pragma once
#include "EntityBase.h"

/*��ʱʵ�����Ϊ�������Լ���������Ҳû�н����ߣ����磺�Ƴ��Լ�
������Ҫһ������������Щ��Ϣ
*/

class SelfMsgReciever :public EntityBase
{
public:
	SelfMsgReciever(int id_) :EntityBase(id_) {}
	~SelfMsgReciever() {}
public:
	virtual bool init() override;

	virtual void clear() override { EntityBase::clear(); }

	virtual void update() override { EntityBase::clear(); }

	static SelfMsgReciever* create();
};
