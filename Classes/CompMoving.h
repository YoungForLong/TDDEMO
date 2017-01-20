#pragma once
#include "cocos2d.h"
#include "CollisionVolume.h"
#include "ComponentBase.h"

using namespace cocos2d;

class CompMoving: public ComponentBase
{
protected:

	//静态的物体或者是动态的物体
	bool _active;
	
	Vec2 _position;
	Vec2 _velocity;//速度
	Vec2 _heading;//朝向
	CollisionVolume _cv;//碰撞体积

	CompMoving* _target;

	Vec2 _aimPos;

#pragma region stors&gtros
public:
	const Vec2 position()const { return _position; }
	void setPostion(const Vec2& pos) { _position = pos; }

	const Vec2 velocity()const { return _velocity; }
	void setVelocity(const Vec2& velocity) { _velocity = velocity; }

	const Vec2 heading()const { return _heading; }
	void setHeading(const Vec2& heading) { _heading = heading; }

	const CollisionVolume getCV()const;

	const CompMoving* target()const { return _target; }
	void setTarget(CompMoving* tar) { _target = tar; }
#pragma endregion

public:
	virtual bool init() override;
	
	virtual void update() override;

protected:
	void moveTo()
};