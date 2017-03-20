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
#include "Lib_Navmesh\FileNavmeshParser.h"
#include "Lib_Navmesh\GraphRender.h"
#include "Lib_Navmesh\AStarSearch.h"

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

	auto bg = LayerColor::create(Color4B::WHITE);
	this->addChild(bg, -10);

	//test navmesh graph
	NavmeshGraph nvmgh;

	nvmgh.loadFromFile("navmesh.json");

	// »­Í¼
	GraphRender render(nvmgh);
	render.init();
	render.addToLayer(this, 1.0f);

	// Ñ°Â·
	AStarSearch pathFinder(nvmgh);

	Vec2 begin(300, 200);
	Vec2 end(800, 600);

	// test
	bool  tag = nvmgh.getNodeById(23)->poly.containsPoint(begin);

	auto node1 = DrawNode::create();
	node1->drawCircle(begin, 2.0f, 360, 30, false, Color4F::MAGENTA);
	this->addChild(node1, 10);
	auto node2 = DrawNode::create();
	node2->drawCircle(end, 2.0f, 360, 30, false, Color4F::GREEN);
	this->addChild(node2, 10);

	auto node = pathFinder.result(begin, end);

	CCLOG("%s","route:");
	for (auto iter = node.cbegin(); iter != node.cend(); ++iter)
	{
		CCLOG("node is: %d", *iter);
		render.drawSolidPoly(*iter);
	}

	auto path = pathFinder.LOS_path(begin, end);
	for (int i = 1; i < path.size(); ++i)
	{
		render.drawLine(Edge(path[i], path[i - 1]), Color4F::GREEN);
	}


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
