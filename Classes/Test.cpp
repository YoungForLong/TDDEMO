#include "Test.h"
#include "MsgDispatcher.h"
#include "ObjectMgr.h"
#include "Cell_Space_Partition.h"
#include "WaterEffect.h"
#include "SeaSprite.h"
#include "EnShip.h"
#include "ComponentDependencies.h"
#include "SelfMsgReciever.h"
#include "GlobalTime.h"
#include "FileNavmeshParser.h"

using namespace recast_navigation;

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

	/*auto ws = Effect::WaterEffect::create("water_pic.png");
	ws->setAnchorPoint(Vec2::ZERO);
	this->addChild(ws, world_sea_zorder);*/

	//test navmesh graph
	NavmeshGraph nvmgh;

	nvmgh.addPoly()

	//_hero = EnShip::create<EnShip>();
	//if (!_hero)
	//	return false;
	//
	//_hero->getComponent<CompMoving>(comp_moving)->setPostion(Vec2(2632, 1536) / 2);

	//auto shower = _hero->getComponent<CompDisplayer>(comp_displayer);
	//shower->setLayer(this, world_above_sea_zorder);


	//
	////other ships
	//srand(time(0));
	//for (int i = 0; i < 10; ++i)
	//{
	//	auto enemyShip = EnShip::create<EnShip>();
	//	if (!enemyShip)
	//		return false;

	//	auto eShower = enemyShip->getComponent<CompDisplayer>(comp_displayer);
	//	eShower->setLayer(this, world_above_sea_zorder);

	//	auto eCm = enemyShip->getComponent<CompMoving>(comp_moving);
	//	eCm->setPostion(Vec2(rand() % 2732, rand() % 1536));
	//}

	////self msg reciever
	//SelfMsgReciever::create();

	////keyboard event
	//auto listener = EventListenerKeyboard::create();

	//listener->onKeyPressed = [this](EventKeyboard::KeyCode code,Event* e) {
	//	_hero->getComponent<CompControllerTest>(comp_controller_test)->onKeyboardPressed(code);
	//};

	//listener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event* e) {
	//	_hero->getComponent<CompControllerTest>(comp_controller_test)->onKeyboardReleased(code);
	//};

	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//this->scheduleUpdate();

	return true;
}

void TestLayer::update(float fl)
{
	MSGDISPATCHER->dispatchMsg();
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
