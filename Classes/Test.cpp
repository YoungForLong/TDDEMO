#include "Test.h"
#include "MsgDispatcher.h"
#include "ObjectMgr.h"
#include "Cell_Space_Partition.h"
#include "WaterEffect.h"
#include "EnShip.h"
#include "ComponentDependencies.h"
#include "SelfMsgReciever.h"
#include "GlobalTime.h"

Scene * TestLayer::createScene()
{
	auto s = Scene::create();
	s->addChild(TestLayer::create(),1,"world");
	return s;
}

bool TestLayer::init()
{
	if (!Layer::init())
		return false;

	_hero = EntityBase::create<EnShip>();
	auto compDis = _hero->getComponent<CompDisplayer>(comp_displayer);
	compDis->setLayer(this, 10);

	auto compCon = _hero->getComponent<CompControllerTest>(comp_controller_test);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [compCon](EventKeyboard::KeyCode code, Event* e)
	{
		compCon->onKeyboardPressed(code);
	};
	listener->onKeyReleased = [compCon](EventKeyboard::KeyCode code, Event* e)
	{
		compCon->onKeyboardReleased(code);
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void TestLayer::update(float fl)
{
	MSGDISPATCHER->update();
	OMGR->updateAll();
	GT->update();
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
