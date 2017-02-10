#include "CompDisplayer.h"
#include "CompMoving.h"
#include "EntityBase.h"
#include <numeric>

bool CompDisplayer::init()
{
	if (!root)
		return false;

	return true;
}

void CompDisplayer::update()
{
	auto moving = root->getComponent<CompMoving>(ComponentType::comp_moving);
	
	if (moving)
	{
		_sprite->setPosition(transformToVisionPosition(moving->position()));
		
		_latestHeadings.push_back(moving->heading());

		if (_latestHeadings.size() == smoothing_frames)
		{
			auto th = accumulate(_latestHeadings.begin(), _latestHeadings.end(), Vec2::ZERO);
			_sprite->setRotation(CU->transformHeadingToRotation(th));
			_latestHeadings.clear();
		}	
	}
}

void CompDisplayer::clear()
{
	_sprite->release();
}

void CompDisplayer::applySprite(ObjectType type)
{
	_sprite = CREATE_SPRITE(spriteNameMap[type]);
	_sprite->retain();
}

Vec2 CompDisplayer::transformToVisionPosition(const Vec2& pos)
{
}
