#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "CollisionVolume.h"

class SlantRect;

class Circle :public CollisionVolume
{
public:
	Circle(float radius, Point center);

	Circle(const Circle& other);

	void setCircle(float radius, Point center);

	bool operator ==(const Circle& other)const
	{
		return ((radius_ == other.radius_) && (center_ == other.center_)) ? true : false;
	}

	Circle& operator =(const Circle& other)
	{
		radius_ = other.radius_;
		center_ = other.center_;
		return *this;
	}

public:
	bool isContainsPoint(const Vec2& point) const;

	bool isIntersectsCircle(Circle* other) const;

	virtual bool intersects(CollisionVolume* other, Vec2& repulsion) override;

	virtual CollisionVolume* realCV(const Vec2& pos, const Vec2& heading) override;

	virtual Vec2 centroid() override;
public:
	float radius_;
	Vec2 center_;
};

#endif