#pragma once
#include "cocos2d.h"
#include "CollisionVolume.h"
#include "ComponentBase.h"

using namespace cocos2d;
using namespace std;

class CompMoving: public ComponentBase
{
protected:

	//��̬����������Ƕ�̬������
	bool _active;

	//�Ƿ��ܴ���
	bool _canCross;
	
	Vec2 _position;
	float _speed;
	Vec2 _velocity;//�ٶ�
	Vec2 _heading;//����
	CollisionVolume _cv;//��ײ���

	CompMoving* _target;

	Vec2 _aimPos;

	//��ײ��⸨������

	//������ײ��
	float _dBoxLength;


#pragma region stors&gtros
public:
	const Vec2 position()const { return _position; }
	void setPostion(const Vec2& pos);

	const float speed()const { return _speed; }
	void setSpeed(const float& spd) { _speed = spd; }

	const Vec2 velocity()const { return _velocity; }
	void setVelocity(const Vec2& velocity) { _velocity = velocity; _heading = _velocity.getNormalized(); }

	const Vec2 heading()const { return _heading; }
	void setHeading(const Vec2& heading) { _heading = heading; }

	const CollisionVolume getCV()const;
	const float getBoundingRadius()const;

	const CompMoving* target()const { return _target; }
	void setTarget(CompMoving* tar) { _target = tar; }
	void setTarget(const Vec2& aim) { _aimPos = aim; }

	const bool isObstacle()const { return _canCross; }

#pragma endregion

public:
	virtual bool init() override;
	
	virtual void update() override;

	virtual void clear() override;

protected://Ϊ��˳���ƶ�ʹ�õĸ�������
	const Vec2 seek(Vec2 aimPos);
	const Vec2 pursuit(CompMoving* target);
	const Vec2 flee(Vec2 aimPos);
	const Vec2 evade(CompMoving* target);
	const Vec2 obstacleAvoidance(vector<CompMoving*>& obstacles);

public:
	void moveTo(Vec2 aimPos);
	void stop();
	void moveTowards(Vec2 h);
};