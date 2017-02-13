#pragma once
#include "EntityBase.h"

/*有时实体的行为不能由自己处理，但是也没有接收者，比如：移除自己
所以需要一个类来处理这些消息
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
