#include "Circle.h"
#include "SlantRect.h"

/*--------------------------------------------- Circle -----------------------------------------------*/
Circle::Circle(float radius, Point center) :
	radius_(radius)
{
	center_ = center;
	type_ = circle;
}

Circle::Circle(const Circle& other)
{
	this->setCircle(other.radius_, other.center_);
}

void Circle::setCircle(float radius, Point center)
{
	radius_ = radius;
	center_ = center;
}

bool Circle::isContainsPoint(const Vec2& point)const
{
	auto disSq = point.getDistanceSq(center_);

	return disSq < (radius_*radius_);
}

bool Circle::isIntersectsCircle(Circle* other)const
{
	auto dis = this->center_.Point::distance(other->center_);

	if (dis < (other->radius_ + this->radius_))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Circle::intersects(CollisionVolume * other, Vec2 & repulsion)
{
	repulsion = other->centroid() - center_;
	if (other->type_ == circle)
	{
		auto cir = static_cast<Circle*>(other);
		
		return isIntersectsCircle(cir);
	}
	else
	{
		auto rect = static_cast<SlantRect*>(other);
		auto s_t_o_l = PointToWorldSpace(center_, rect->heading(), rect->heading().getPerp(), rect->originRect().origin);

		return Rect(Vec2::ZERO, rect->originRect().size).intersectsCircle(s_t_o_l, radius_);
	}
}

CollisionVolume * Circle::realCV(const Vec2 & pos, const Vec2 & heading)
{
	center_ = pos;
	return this;
}

Vec2 Circle::centroid()
{
	return center_;
}
