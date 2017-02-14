#ifndef _COMP_BATTLE_H_
#define _COMP_BATTLE_H_

#include "ComponentBase.h"

typedef struct 
{
	int hp_;//����
	int damage_;//�˺�
	int armour_;//����
	float attackDuration_;//�������
	int attackLimit_;//��������
}BattleConfig, *BattleConfigPtr;

class CompBattle :public ComponentBase
{
public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;

	/*normal attack
	@param targetId Ŀ��id
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

	//һ���˽���������ʾ��ǰ��������״̬
	int _bonusFlag;

	ObjectType _bulletType;
};


#endif