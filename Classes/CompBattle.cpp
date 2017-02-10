#include "CompBattle.h"
#include "GlobalTime.h"
#include "ObjectMgr.h"
#include "CompMoving.h"
#include "EnBullet.h"

using namespace cocos2d;

bool CompBattle::init()
{
	if (!root)
		return false;

	simOriginInfo();

	_hp = _originConfig.hp_;
	_damage = _originConfig.damage_;
	_attackLimit = _originConfig.attackLimit_;
	_attackDuration = _originConfig.attackDuration_;
	_armour = _originConfig.armour_;
}

void CompBattle::update()
{
	//¹¥»÷ÀäÈ´
	_attackCoolDown -= GT->deltaTime;
	_attackCoolDown = _attackCoolDown > 0 ? _attackCoolDown : 0;
}

void CompBattle::clear()
{
}

void CompBattle::normalAttack(int targetId)
{
	if (_attackCoolDown != 0)
	{
		auto target = OMGR->getEntityById(targetId);
		
	}
}

void CompBattle::onAttacked()
{
}

void CompBattle::simOriginInfo()
{
	_originConfig.armour_ = 1;
	_originConfig.attackDuration_ = 1.2f;
	_originConfig.attackLimit_ = 600;
	_originConfig.damage_ = 4;
	_originConfig.hp_ = 40;
}

int CompBattle::calculateDamage(int damage)
{
	//ÉËº¦ = ¹¥»÷ - »¤¼×
	int finalDamage = damage - _armour;

	finalDamage = finalDamage > 1 ? finalDamage : 1;

	return finalDamage;
}
