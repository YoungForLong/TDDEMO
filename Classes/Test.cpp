#include "Test.h"
#include "MsgDispatcher.h"
#include "ObjectMgr.h"
#include "Cell_Space_Partition.h"
#include "CompDisplayer.h"
#include "CompCommunicator.h"
#include "CompMoving.h"
#include "WaterEffect.h"

Scene * TestLayer::createScene()
{
	auto s = Scene::create();
	s->addChild(TestLayer::create());
	return s;
}

bool TestLayer::init()
{
	/*CSP->init(Rect(0, 0, WHOLE_MAP_WIDTH, WHOLE_MAP_HEIGHT), 10, 10);

	_entity1 = EntityBase::create<EntityBase>();
	auto moving = _entity1->addComponent<CompMoving>(ComponentType::comp_moving);
	_entity1->addComponent<CompCommunicator>(ComponentType::comp_communicator);
	auto s = _entity1->addComponent<CompDisplayer>(ComponentType::comp_displayer);
	moving->setSpeed(100);
	moving->setTarget(Vec2(2000, 1000));
	s->setLayer(this);

	srand(time(0));
	for (int i = 0; i < 100; ++i)
	{
		auto entity = EntityBase::create<EntityBase>();
		auto mov = entity->addComponent<CompMoving>(ComponentType::comp_moving);
		auto sp = entity->addComponent<CompDisplayer>(ComponentType::comp_displayer);
		sp->setLayer(this);

		mov->setPostion(Vec2(100 + rand() % 2000, 100 + rand() % 1000));
	}*/
	srand(time(0));

	auto water = Effect::WaterEffect::create("water_pic_1.png");
	water->setAnchorPoint(Vec2::ZERO);
	/*water->setScale(10);*/
	water->retain();
	this->addChild(water, bg_zorder);
	_we = water->getGLProgramState();

	_testShip = Sprite::create("test_ship.png");
	_testShip->setPosition(Director::getInstance()->getWinSize() / 2);
	_testShip->setScale(2);
	this->addChild(_testShip, 10);
	
	for (int i = 0; i < 4; ++i)
	{
		auto bgSp = Sprite::create("test_ship.png");
		bgSp->setPosition(Vec2(100 + rand() % 2000, 100 + rand() % 1000));
		bgSp->setRotation(rand() % 360);
		bgSp->setScale(2);
		this->addChild(bgSp, 10);
		_bgSps.push_back(bgSp);
	}

	addTouchReact();

	this->scheduleUpdate();

	return true;
}

void TestLayer::update(float fl)
{
	if(_toTarget.getLengthSq()>0.1f)
	{
		const float speed = 4;
		
		const float factor = 0.1f;

		for (auto iter = _bgSps.begin(); iter != _bgSps.end(); ++iter)
		{
			auto oldPos = (*iter)->getPosition();
			auto delta = -1 * _toTarget.getNormalized()*speed;

			(*iter)->setPosition(oldPos + delta);
		}

		if (_toTarget.getLengthSq() > speed*speed)
			_toTarget -= _toTarget.getNormalized()*speed;
		else
			_toTarget = Vec2::ZERO;
	}
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

		_toTarget = touchPos - Director::getInstance()->getWinSize() / 2;

		_testShip->setRotation(-_toTarget.getAngle() * 180 / PI - 170);
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}
