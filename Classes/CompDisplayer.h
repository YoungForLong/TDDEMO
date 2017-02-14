#ifndef _SHOWER_H_
#define _SHOWER_H_
#include "ComponentBase.h"
#include "cocos2d.h"
#include "CommonUtils.h"

using namespace cocos2d;

class CompDisplayer :public ComponentBase
{
public:
	std::map<ObjectType, string> spriteNameMap =
	{
		make_pair<ObjectType,string>(stone_bullet,"stone_bullet.png"),
		make_pair<ObjectType,string>(ship,"test_ship.png"),
	};

public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;

	void applySprite(ObjectType type);

	void setLayer(Layer* layer, int zorder) { layer->addChild(_sprite, zorder); }

	Vec2 transformToVisionPosition(const Vec2& pos);
private:
	//textures: pictures, particles, bones
	Sprite* _sprite;
	
	std::vector<Vec2> _latestHeadings;
};

#endif
