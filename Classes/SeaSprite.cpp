#include "SeaSprite.h"

void SeaSprite::init()
{
	_parent = nullptr;
	_layerOnly = false;
}

bool SeaSprite::addSeaEffect(Layer* parent)
{
	_parent = parent;

	if (_layerOnly)
	{
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		auto sp = Effect::WaterEffect::create(StringUtils::format("water_pic_%d.png", i + 1));
		sp->setAnchorPoint(Vec2::ZERO);
		parent->addChild(sp, bg_zorder);
		_seaLands.push_back(sp);
	}

	setLayoutByPos(Vec2::ZERO);

	_layerOnly = true;

	return true;
}

void SeaSprite::updateByHeroPosition(const Vec2 & pos)
{
	setLayoutByPos(pos);
}

void SeaSprite::setLayoutByPos(const Vec2 & center)
{
	Vec2 rectOrigin = center - Vec2(2732, 1536) / 2;

	int xOrder = int(rectOrigin.x) / 2732;
	int yOrder = int(rectOrigin.y) / 1536;

	int xRemainder = int(rectOrigin.x) % 2732;
	int yRemainder = int(rectOrigin.y) % 1536;

	//屏幕左下角对应的图片编号
	int originOrder = xOrder % 2 + yOrder % 2 + 1;

	//编号数组
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

	auto originPos = -1 * Vec2(xRemainder, yRemainder);
	for (int i = 0; i < 4; ++i)
	{
		Vec2 eachPos = originPos + Vec2(2732 * ((i) % 2), 1536 * ((i) / 2));
		_seaLands.at(targetArr[i] - 1)->setPosition(eachPos);
	}
}

