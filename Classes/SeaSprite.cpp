#include "SeaSprite.h"

bool SeaSprite::addSeaEffect(Layer* parent)
{
	if (_layerOnly)
	{
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		auto sp = Effect::WaterEffect::create(StringUtils::format("water_pic_%d.png", i + 1).c_str());
	}

	setLayoutByPos(Vec2::ZERO);

	_layerOnly = true;

	return true;
}

void SeaSprite::updateByHeroPosition(const Vec2 & pos)
{
}

void SeaSprite::setLayoutByPos(const Vec2 & center)
{
	Vec2 rectOrigin = center - Vec2(2732, 1536) / 2;

	int xOrder = int(rectOrigin.x) / 2732;
	int yOrder = int(rectOrigin.y) / 1536;

	int xRemainder = int(rectOrigin.x) % 2732;
	int yRemainder = int(rectOrigin.y) % 1536;

	//ÆÁÄ»×óÏÂ½Ç¶ÔÓ¦µÄÍ¼Æ¬±àºÅ
	int originOrder = xOrder % 2 + yOrder % 2 + 1;

	//±àºÅÊý×é
	int orderArr_1[] = { 1,2,3,4 };
	int orderArr_2[] = { 2,1,4,3 };
	int orderArr_3[] = { 3,4,1,2 };
	int orderArr_4[] = { 4,3,2,1 };

	auto* targetArr = orderArr_1;

	switch (originOrder)
	{
	case 1:
		targetArr = orderArr_1;
		break;
	case 2:
		targetArr = orderArr_2;
		break;
	case 3:
		targetArr = orderArr_3;
		break;
	case 4:
		targetArr = orderArr_4;
		break;
	default:
		assert(0 && "Error: wrong order");
		break;
	}

	auto originPos = Vec2(xRemainder, yRemainder) - Vec2(2732, 1536);
	for (int i = 0; i < 4; ++i)
	{
		Vec2 eachPos = 
		_seaLands.at(targetArr[i] - 1)->setPosition(eachPos);
	}
}

