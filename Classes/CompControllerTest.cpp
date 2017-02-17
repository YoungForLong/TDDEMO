#include "ComponentDependencies.h"
#include "EntityBase.h"
#include "Cell_Space_Partition.h"
#include <numeric>

bool CompControllerTest::init()
{
	if (!root)
		return false;
	return true;
}

void CompControllerTest::update()
{
	if (_curKeyState == 0)
		return;

	auto cm = root->getComponent<CompMoving>(comp_moving);

	switch (_curKeyState)
	{
	case 1:
		cm->moveTowards(Vec2::UNIT_Y);
		break;
	case 2:
		cm->moveTowards(-Vec2::UNIT_X);
		break;
	case 3:
		cm->moveTowards(-Vec2::UNIT_Y);
		break;
	case 4:
		cm->moveTowards(Vec2::UNIT_X);
		break;
	case 5:
		attack();
		break;
	default:
		break;
	}
}

void CompControllerTest::clear()
{
}

void CompControllerTest::onKeyboardPressed(cocos2d::EventKeyboard::KeyCode code)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		_curKeyState = 5;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_curKeyState = 1;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_curKeyState = 2;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_curKeyState = 3;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_curKeyState = 4;
		break;
	default:
		break;
	}
}

void CompControllerTest::onKeyboardReleased(cocos2d::EventKeyboard::KeyCode code)
{
	_curKeyState = 0;

	/*if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		auto& arrRef = CU->testNumArr;

		float aver = accumulate(arrRef.begin(), arrRef.end(), 0.0f) / arrRef.size();

		CCLOG("averange obs force: %f", aver);

		CCDirector::getInstance()->end();
	}*/
}

bool CompControllerTest::attack()
{
	auto cb = root->getComponent<CompBattle>(comp_battle);
	auto selfCm = root->getComponent<CompMoving>(comp_moving);

	auto neighbors = CSP->getNeighbors(root->getComponent<CompMoving>(comp_moving), 1200);
	if (neighbors.empty())
		return false;

	//find the nearest one
	float distSq = max_float;
	CompMoving* nearestCm = nullptr;
	for_each(neighbors.cbegin(), neighbors.cend(), [&distSq, &nearestCm, selfCm](CompMoving* eachCm) {
		auto curDistSq = selfCm->position().getDistanceSq(eachCm->position());
		if (distSq > curDistSq)
		{
			distSq = curDistSq;
			nearestCm = eachCm;
		}
	});

	if (nearestCm == nullptr)
		return false;

	return cb->normalAttack(nearestCm->root->id());
}
