#ifndef _EN_SHIP_H_
#define _EN_SHIP_H_

#include "EntityBase.h"

class EnShip :public EntityBase
{
public:
	EnShip(int id_) :EntityBase(id_) { _type = ship; }
	~EnShip() {}
public:
	virtual bool init() override;

	virtual void update() override;

	virtual void clear() override;
};



#endif
