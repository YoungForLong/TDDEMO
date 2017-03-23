#ifndef _SHOWER_H_
#define _SHOWER_H_
#include "ComponentBase.h"
#include "cocos2d.h"
#include "CommonUtils.h"

using namespace cocos2d;

class CompDisplayer :public ComponentBase
{
public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;

	void applySprite(ObjectType type);

	void applySprite(const string& filename);

	void setLayer(Layer* layer, int zorder) { layer->addChild(_sprite, zorder); }

	Vec2 transformToVisionPosition(const Vec2& pos);
private:
	//textures: pictures, particles, bones
	Sprite* _sprite;

	std::queue<Vec2> _latestHeadings;
};

#endif
