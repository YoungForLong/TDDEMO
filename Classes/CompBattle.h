#ifndef _COMP_BATTLE_H_
#define _COMP_BATTLE_H_

#include "ComponentBase.h"

typedef struct 
{
	int hp_;//生命
	int damage_;//伤害
	int armour_;//护甲
	float attackDuration_;//攻击间隔
	int attackLimit_;//攻击距离
}BattleConfig, *BattleConfigPtr;

class CompBattle :public ComponentBase
{
public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;

	/*normal attack
	@param targetId 目标id
	@return is attacking succ
	*/
	bool normalAttack(int targetId);

	void onAttacked();
private:

#pragma region test
	
	void simOriginInfo();

#pragma endregion
	
	int calculateDamage(int damage);

	bool isAttackCoolDown() const { return _attackCoolDown; }
private:
	BattleConfig _originConfig;
	
	int _hp;
	int _damage;
	int _armour;
	float _attackDuration;
	int _attackLimit;

	long _attackCoolDown;

	//一个八进制数来表示当前攻击附加状态
	int _bonusFlag;

	ObjectType _bulletType;
};


#endif