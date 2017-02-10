#ifndef _EN_BULLET_H_
#define _EN_BULLET_H_

#include "EntityBase.h"

typedef struct
{
	int source_ = illegal_id;
	int target_ = illegal_id;
	int typeFlag_ = 0x0001;

	Vec2 heading_;
	Vec2 position_;
	ObjectType type_;

	bool isNull()
	{
		return source_ == illegal_id && target_ == illegal_id;
	}
}AttackInfo, *AttackInfoPtr;

class EnBullet :public EntityBase
{
private:
	EnBullet(int id_) :EntityBase(id_) { _type = bullet; }
	~EnBullet() {}
public:
	virtual bool init() override;

	virtual void update() override;

	virtual void clear() override;

	//Ϊ�ӵ������Ϣ
	void addInfo(const AttackInfo& info);

protected:
	//�ӵ�����Ŀ��
	void flyToAim();

	//�Ƴ��Լ�(����һִ֡��)
	void destroySelf();
private:
	AttackInfo _attackInfo;
};


#endif
