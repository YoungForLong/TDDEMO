#ifndef _OBJECT_BASE_H_
#define _OBJECT_BASE_H_

#include "cocos2d.h"
#include "CommonEnum.h"

using namespace cocos2d;
using namespace std;

class ObjectBase
{
public:
	ObjectBase(int id_) :_id(id_) {}
	virtual ~ObjectBase() {}
public:
	const int id()const { return _id; }
	const ObjectType type()const { return _type; }

	virtual void update() = 0;
	virtual void clear() = 0;
protected:
	int _id;
	ObjectType _type;
};



#endif