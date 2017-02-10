#pragma once

#include "cocos2d.h"
#include "WaterEffect.h"
#include "Singleton.h"
#include "CommonEnum.h"

USING_NS_CC;
using namespace std;

class SeaSprite :public Singleton<SeaSprite>
{
public:
	void init();
	bool addSeaEffect(Layer* parent);
	void updateByHeroPosition(const Vec2& pos);
protected:
	void setLayoutByPos(const Vec2& center);
private:
	vector<Effect::WaterEffect*> _seaLands;
	static SeaSprite* _instance;
	bool _layerOnly;
	Layer* _parent;
};