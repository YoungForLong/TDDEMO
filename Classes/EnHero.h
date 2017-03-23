#ifndef _EN_HERO_H_
#define _EN_HERO_H_

#include "EnShip.h"

class EnHero :public EnShip
{
public:
	EnHero(int id):EnShip(hero_id) {}
};

#endif
