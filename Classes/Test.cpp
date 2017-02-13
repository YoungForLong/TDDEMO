#include "Test.h"
#include "MsgDispatcher.h"
#include "ObjectMgr.h"
#include "Cell_Space_Partition.h"
#include "CompDisplayer.h"
#include "CompCommunicator.h"
#include "CompMoving.h"
#include "WaterEffect.h"
#include "SeaSprite.h"
#include "EnShip.h"

Scene * TestLayer::createScene()
{
	auto s = Scene::create();
	s->addChild(TestLayer::create());
	return s;
}

bool TestLayer::init()
{
	if (!Layer::init())
		return false;

	auto ws = Effect::WaterEffect::create("water_pic_1.png");
	ws->setAnchorPoint(Vec2::ZERO);
	this->addChild(ws, world_sea_zorder);

	_hero = EnShip::create<EnShip>();
	if (!_hero)
		return false;
	
	auto shower = _hero->getComponent<CompDisplayer>(comp_displayer);
	shower->setLayer(this);

	return true;
}

void TestLayer::update(float fl)
{
	OMGR->updateAll();
}

void TestLayer::addTouchReact()
{
	auto eventListener = EventListenerTouchOneByOne::create();

	eventListener->onTouchBegan = [](Touch* touch, Event* e)
	{
		return true;
	};

	eventListener->onTouchEnded = [this](Touch* touch, Event* e)
	{
		auto touchPos = touch->getLocation();

		
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}
