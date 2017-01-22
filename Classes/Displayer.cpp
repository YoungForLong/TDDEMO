#include "Displayer.h"
#include "CompMoving.h"
#include "EntityBase.h"
#include <numeric>

bool Displayer::init()
{
	_sprite = Sprite::create("CloseNormal.png");
	_sprite->retain();

	return true;
}

void Displayer::update()
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

void Displayer::clear()
{
	_sprite->release();
}

void Displayer::transformToRotation(Vec2 heading)
{
	_sprite->setRotation(heading.getAngle()*180 / PI + 25);
}
