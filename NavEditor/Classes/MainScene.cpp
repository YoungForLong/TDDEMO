#include "MainScene.h"

bool MainScene::init()
{
	if(!Layer::init())
		return false;

	_vertsAndEdges = Sprite::create();
	this->addChild(_vertsAndEdges, 10);

	addStaticStyle();

	addTouchReaction();

	return true;
}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	scene->addChild(MainScene::create());
	return scene;
}

void MainScene::addStaticStyle()
{
	const int bg_z_order = -1;
	auto bg = LayerColor::create(Color4B::WHITE);
	this->addChild(bg, bg_z_order);

	auto sp = Sprite::create("navmesh_test.png");
	sp->setAnchorPoint(Vec2::ZERO);
	sp->setScale(0.5f);
	
	this->addChild(sp, 0);
}

void MainScene::addTouchReaction()
{
	auto eventListener = EventListenerTouchOneByOne::create();
	
	eventListener->onTouchBegan = [this](Touch* touch,Event* e)->bool {
		auto pos = touch->getLocation();

		if (!this->isAlreadyExist(pos))
		{
			this->drawPoint(pos);
		}

		this->constructPoly(pos);
		
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	//³·Ïú¹¦ÄÜ
	auto keyListener = EventListenerKeyboard::create();

	keyListener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* e) {
		if (code == EventKeyboard::KeyCode::KEY_K)
		{
			cancel();
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void MainScene::drawPoint(const Vec2& point)
{
	const float r = 2.0f;
	const float point_z_order = 10;

	auto node = DrawNode::create();
	node->drawCircle(point, 2.0f, 360, 30, false, Color4F::BLUE);
	
	Vec2_Node nodeWithPos;
	nodeWithPos._key = point;
	nodeWithPos._value = node;
	_nodeMap.push_back(nodeWithPos);

	_vertsAndEdges->addChild(node, 10);
}

void MainScene::drawPoly(const ConvexPolygon& poly)
{
	auto lastPoint = poly.vertexArr.at(0);
	auto size = poly.vertexArr.size();
	for (int i = 1; i < size; ++i)
	{
		auto curPoint = poly.vertexArr.at(i);
		drawLine(lastPoint, curPoint);
		lastPoint = curPoint;
	}

	drawLine(lastPoint, poly.vertexArr.at(0));
}

void MainScene::drawLine(const Vec2 & from, const Vec2 & to)
{
	auto render = DrawNode::create();
	render->drawLine(from, to, Color4F::RED);

	_vertsAndEdges->addChild(render, 9);
}

void MainScene::drawSolidPoly(const ConvexPolygon & poly)
{
	auto render = DrawNode::create();

	int length = poly.vertexArr.size();
	Vec2* vertArr = new Vec2[length];
	for (int i = 0; i < length; ++i)
	{
		vertArr[i] = poly.vertexArr.at(i);
	}

	render->drawSolidPoly(vertArr, length, Color4F::GREEN);
	
	_vertsAndEdges->addChild(render, 5);
	_polysInView.push_back(render);
}

void MainScene::save()
{
}

bool MainScene::isAlreadyExist(Vec2 & point)
{
	for (auto iter = _nodeMap.begin(); iter != _nodeMap.end(); ++iter)
	{
		if (iter->_key.getDistanceSq(point) < presion*presion)
		{
			point = iter->_key;
			return true;
		}
	}
}

bool MainScene::constructPoly(const Vec2 & point)
{
	if (_currentVerts.size() != 0)
	{
		if (point.distanceSquared(_currentVerts.at(0)) < presion*presion)
		{
			CCLOG("Poly: ");
			for (auto iter = _currentVerts.begin(); iter != _currentVerts.end(); ++iter)
			{
				CCLOG("Verts: %f, %f", iter->x, iter->y);
			}

			ConvexPolygon poly(_currentVerts);
			_polys.push_back(poly);
			drawPoly(poly);
			drawSolidPoly(poly);

			_currentVerts.clear();
			return true;
		}
	}

	_currentVerts.push_back(point);
	return false;
}

void MainScene::cancel()
{
	if (!this->_currentVerts.empty())
	{
		this->_currentVerts.pop_back();

		auto sp = this->_nodeMap.at(this->_nodeMap.size() - 1);
		this->_nodeMap.pop_back();

		this->_vertsAndEdges->removeChild(sp._value, true);
	}
}

