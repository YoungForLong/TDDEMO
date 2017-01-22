#ifndef _SHOWER_H_
#define _SHOWER_H_
#include "ComponentBase.h"
#include "cocos2d.h"

using namespace cocos2d;

class Displayer :public ComponentBase
{
public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;

	void setLayer(Layer* layer) { layer->addChild(_sprite); }

	void transformToRotation(Vec2 heading);
private:
	Sprite* _sprite;
	
	std::vector<Vec2> _latestHeadings;
};

#endif
