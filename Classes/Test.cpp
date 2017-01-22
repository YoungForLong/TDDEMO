#include "Test.h"
#include "MsgDispatcher.h"
#include "ObjectMgr.h"
#include "Cell_Space_Partition.h"
#include "Displayer.h"
#include "CompCommunicator.h"
#include "CompMoving.h"

Scene * TestLayer::createScene()
{
	auto s = Scene::create();
	s->addChild(TestLayer::create());
	return s;
}

bool TestLayer::init()
{
	CSP->init(Rect(0, 0, WHOLE_MAP_WIDTH, WHOLE_MAP_HEIGHT), 10, 10);

	_entity1 = EntityBase::create<EntityBase>();
	auto moving = _entity1->addComponent<CompMoving>(ComponentType::comp_moving);
	_entity1->addComponent<CompCommunicator>(ComponentType::comp_communicator);
	auto s = _entity1->addComponent<Displayer>(ComponentType::comp_displayer);
	moving->setSpeed(100);
	moving->setTarget(Vec2(2000, 1000));
	s->setLayer(this);

	srand(time(0));
	for (int i = 0; i < 100; ++i)
	{
		auto entity = EntityBase::create<EntityBase>();
		auto mov = entity->addComponent<CompMoving>(ComponentType::comp_moving);
		auto sp = entity->addComponent<Displayer>(ComponentType::comp_displayer);
		sp->setLayer(this);

		mov->setPostion(Vec2(100 + rand() % 2000, 100 + rand() % 1000));
	}

	this->scheduleUpdate();

	return true;
}

void TestLayer::update(float fl)
{
	MSGDISPATCHER->dispatchMsg();
	OMGR->updateAll();
}
