#pragma once
#include "EntityBase.h"

/*��ʱʵ�����Ϊ�������Լ���������Ҳû�н����ߣ����磺�Ƴ��Լ�
������Ҫһ������������Щ��Ϣ
*/

class SelfMsgReciever :public EntityBase
{
public:
	SelfMsgReciever() :EntityBase(selfMsgReceiver_id) {}
	~SelfMsgReciever() {}
public:
	virtual bool init() override;

	virtual void clear() override { EntityBase::clear(); }

	virtual void update() override { EntityBase::update(); }

	static SelfMsgReciever* create();
};
