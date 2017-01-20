#include "CompMoving.h"

bool CompMoving::init()
{
	_position = Vec2::ZERO;
	_velocity = Vec2::ZERO;
	_heading = Vec2::ZERO;
	_cv = CollisionVolume();

	return false;
}

const CollisionVolume CompMoving::getCV()const
{
	CollisionVolume CV;
	int count = 0;
	while (count < _cv.circle_.size())
	{
		Circle c1 = _cv.circle_[count];
		CV.circle_.push_back(Circle(c1.radius_, c1.center_ + _position, 0, 360));
		count++;
	}
	count = 0;
	while (count < _cv.rect_.size())
	{
		Rect r1 = _cv.rect_[count];
		CV.rect_.push_back(Rect(r1.origin.x + _position.x, r1.origin.y + _position.y, r1.size.width, r1.size.height));
		count++;
	}
}