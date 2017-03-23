#ifndef _EN_ENVIRONMENT_H_
#define _EN_ENVIRONMENT_H_

#include "EntityBase.h"

class EnEnvironment : public EntityBase
{
public:
	EnEnvironment(int id_) :EntityBase(id_) { _type = environment; }
	~EnEnvironment() {}
	
public:
	virtual bool init() override;

	virtual void update() override;

	virtual void clear() override;
};

#endif