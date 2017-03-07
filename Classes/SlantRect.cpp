#include "SlantRect.h"
#include "Circle.h"

SlantRect::SlantRect(const Rect& origin, const Vec2& heading) :
	_originRect(origin),
	_heading(heading)
{}

SlantRect::SlantRect(const SlantRect& other)
{
	_originRect = other._originRect;
	_heading = other._heading;
}

SlantRect SlantRect::cloneTo(const Vec2 origin) const
{
	return SlantRect(Rect(origin, this->_originRect.size), this->_heading);
}

CollisionVolume * SlantRect::realCV(const Vec2 & pos, const Vec2 & heading)
{
	_originRect.origin = pos;
	_heading = heading;
	return this;
}

bool SlantRect::intersects(CollisionVolume * other, Vec2 & repulsion)
{
	if (other->type_ == circle)
	{
		auto cir = static_cast<Circle*>(other);
		return intersectCircle(cir, repulsion);
	}
	else if (other->type_ == slant_rect)
	{
		auto sr = static_cast<SlantRect*>(other);
		return intersectRect(sr, repulsion);
	}
}

void SlantRect::rotate(float radian)
{
	_heading.rotateByAngle(Vec2::ZERO, radian);
}

bool SlantRect::intersectRect(SlantRect* other, Vec2 & rv) const
{
	auto selfQ = this->FourVertex();
	auto otherQ = other->FourVertex();

	//先检测aabb
	if (!selfQ.get_aabb_box().intersectsRect(otherQ.get_aabb_box()))
	{
		return false;
	}

	//再检测四个点

	//先转化到本地坐标系
	auto o_h_t_s_l = VectorToLocalSpace(other->heading(), _heading, _heading.getPerp());
	auto o_o_t_s_l = PointToLocalSpace(other->originRect().origin, _heading, _heading.getPerp(), _originRect.origin);
	auto otherOnLocal = SlantRect(Rect(o_o_t_s_l, other->originRect().size), o_h_t_s_l);

	vector<Vec2> contains;

	auto newOtherQ = otherOnLocal.FourVertex();
	auto localRect = Rect(Vec2::ZERO, _originRect.size);

	if (localRect.containsPoint(newOtherQ.a))
	{
		contains.push_back(newOtherQ.a);
	}
	if (localRect.containsPoint(newOtherQ.b))
	{
		contains.push_back(newOtherQ.b);
	}
	if (localRect.containsPoint(newOtherQ.c))
	{
		contains.push_back(newOtherQ.c);
	}
	if (localRect.containsPoint(newOtherQ.d))
	{
		contains.push_back(newOtherQ.d);
	}

	if (contains.size() > 0)
	{
		//斥力点近似处理为包含点的平均点
		auto rp = accumulate(contains.begin(), contains.end(), Vec2::ZERO) / contains.size();
		//质心
		auto otherPivot = (newOtherQ.a + newOtherQ.b + newOtherQ.c + newOtherQ.d) / 4;

		//斥力方向 = 斥力点 - 排斥物质心
		auto localRvD = rp - otherPivot;

		//斥力大小正比于交点到本物体质心的距离,此处近似处理为两物体质心距离
		auto selfPivot = Vec2(_originRect.size) / 2;
		auto localRv = localRvD.getNormalized()*selfPivot.getDistance(otherPivot);

		rv = VectorToWorldSpace(localRv, _heading, _heading.getPerp());

		return true;
	}
	else
	{
		//把self转化到other的本地坐标系
		auto s_h_t_o_l = VectorToLocalSpace(_heading, other->heading(), other->heading().getPerp());
		auto s_o_t_o_l = PointToLocalSpace(_originRect.origin, other->heading(), other->heading().getPerp(), other->originRect().origin);
		auto selfOnLocal = SlantRect(Rect(s_o_t_o_l, _originRect.size), s_h_t_o_l);

		auto newSelfQ = selfOnLocal.FourVertex();

		if (localRect.containsPoint(newSelfQ.a))
		{
			contains.push_back(newSelfQ.a);
		}
		if (localRect.containsPoint(newSelfQ.b))
		{
			contains.push_back(newSelfQ.b);
		}
		if (localRect.containsPoint(newSelfQ.c))
		{
			contains.push_back(newSelfQ.c);
		}
		if (localRect.containsPoint(newSelfQ.d))
		{
			contains.push_back(newSelfQ.d);
		}

		if (contains.size() > 0)
		{
			auto rp = accumulate(contains.begin(), contains.end(), Vec2::ZERO) / contains.size();
			auto pivot = Vec2(other->originRect().size) / 2;

			auto selfPivot = (newSelfQ.a + newSelfQ.b + newSelfQ.c + newSelfQ.d) / 4;

			auto localRv = (rp - pivot).getNormalized()*pivot.getDistance(selfPivot);

			rv = VectorToWorldSpace(localRv, other->heading(), other->heading().getPerp());

			return true;
		}
	}

	return false;
}

bool SlantRect::intersectCircle(Circle* other, Vec2 rv) const
{
	rv = other->center_;
	auto o_t_s_l = PointToWorldSpace(other->center_, _originRect.origin, _heading, _heading.getPerp());
	return _originRect.intersectsCircle(o_t_s_l, other->radius_);
}

Vec2 SlantRect::centroid()
{
	auto temp = FourVertex();

	return (temp.a + temp.b + temp.c + temp.d) / 4;
}

Quadrangle SlantRect::FourVertex() const
{
	Vec2 originA = _originRect.origin;
	Vec2 originB = originA + Vec2(0, _originRect.size.height);
	Vec2 originC = originA + _originRect.size;
	Vec2 originD = originA + Vec2(_originRect.size.width, 0);

	Quadrangle temp;

	temp.a = originA.rotate(_heading);
	temp.b = originB.rotate(_heading);
	temp.c = originC.rotate(_heading);
	temp.d = originD.rotate(_heading);

	return temp;
}
