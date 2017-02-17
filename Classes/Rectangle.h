#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "cocos2d.h"
#include "Tranformation.h"

USING_NS_CC;

class Rectangle
{
#pragma region ctors & cloner
public:
	Rectangle(const Rect& origin, const Vec2& heading) :
		originRect_(origin),
		heading_(heading)
	{}

	~Rectangle() = default;

	Rectangle(const Rectangle& other)
	{
		originRect_ = other.originRect_;
		heading_ = other.heading_;
	}

	Rectangle& operator = (const Rectangle& other)
	{
		this->originRect_ = other.originRect_;
		this->heading_ = other.heading_;
		return *this;
	}

	bool operator == (const Rectangle other)const
	{
		return (originRect_.equals(other.originRect_)) &&
			(heading_ == other.heading_);
	}
#pragma endregion

public:


public:
	Rect originRect_;
	Vec2 heading_;
};


#endif
