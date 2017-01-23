#include "CompDisplayer.h"
#include "CompMoving.h"
#include "EntityBase.h"
#include <numeric>

bool CompDisplayer::init()
{
	_sprite = Sprite::create("CloseNormal.png");
	_sprite->retain();

	return true;
}

void CompDisplayer::update()
{
	auto moving = root->getComponent<CompMoving>(ComponentType::comp_moving);
	
	if (moving)
	{
		_sprite->setPosition(moving->position());
		
		_latestHeadings.push_back(moving->heading());

		if (_latestHeadings.size() == smoothing_frames)
		{
			auto th = accumulate(_latestHeadings.begin(), _latestHeadings.end(), Vec2::ZERO);
			transformToRotation(th);
			_latestHeadings.clear();
		}	
	}
}

void CompDisplayer::clear()
{
	_sprite->release();
}

void CompDisplayer::transformToRotation(Vec2 heading)
{
	_sprite->setRotation(90 - heading.getAngle() * 180 / PI);
}
