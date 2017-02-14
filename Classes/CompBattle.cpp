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

	_attackCoolDown = 0;
	_bonusFlag = 0x0001;

	//test
	_bulletType = stone_bullet;
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

bool CompBattle::normalAttack(int targetId)
{
	if (_attackCoolDown <= 0)
	{
		auto target = OMGR->getEntityById(targetId);
		auto targetCm = target->getComponent<CompMoving>(comp_moving);
		auto selfCm = root->getComponent<CompMoving>(comp_moving);
		
		if (targetCm->position().getDistanceSq(selfCm->position()) < _attackLimit * _attackLimit)
		{
			//create bullet
			AttackInfo info;
			info.heading_ = selfCm->heading();
			info.position_ = selfCm->position();
			info.source_ = root->id();
			info.target_ = targetId;
			info.typeFlag_ = _bonusFlag;
			info.type_ = _bulletType;

			auto bullet = EnBullet::create<EnBullet>();
			bullet->addInfo(info);
			bullet->flyToAim();

			_attackCoolDown = _originConfig.attackDuration_ * 1000;

			return true;
		}
	}

	return false;
}

void CompBattle::onAttacked()
{
	log("on attacked!");
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
