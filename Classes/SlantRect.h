#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "cocos2d.h"
#include "Tranformation.h"
#include "CommonUtils.h"
#include <numeric>

USING_NS_CC;

/*descrip a Quadrangle by its four vertex in clock-wise order
*/
typedef struct {
	Vec2 a;
	Vec2 b;
	Vec2 c;
	Vec2 d;

	//AABB funcs
	Rect get_aabb_box()
	{
		float minX = CU->multiMin(a.x, b.x, c.x, d.x);
		float minY = CU->multiMin(a.y, b.y, c.y, d.y);
		float maxX = CU->multiMax(a.x, b.x, c.x, d.x);
		float maxY = CU->multiMax(a.y, b.y, c.y, d.y);

		return Rect(minX, minY, maxX - minX, maxY - minY);
	}
}Quadrangle, *PtrQuadrangle;

class SlantRect: public CollisionVolume
{
#pragma region ctors & cloner
public:
	SlantRect(const Rect& origin, const Vec2& heading) :
		_originRect(origin),
		_heading(heading)
	{}

	~SlantRect() = default;

	SlantRect(const SlantRect& other)
	{
		_originRect = other._originRect;
		_heading = other._heading;
	}

	SlantRect cloneTo(const Vec2 origin) const
	{
		return SlantRect(Rect(origin, this->_originRect.size), this->_heading);
	}

	SlantRect& operator = (const SlantRect& other)
	{
		this->_originRect = other._originRect;
		this->_heading = other._heading;
		return *this;
	}

	bool operator == (const SlantRect other) const
	{
		return (_originRect.equals(other._originRect)) &&
			(_heading == other._heading);
	}

	bool operator != (const SlantRect other) const
	{
		return !(*this == other);
	}
#pragma endregion

public:

	/*rotate the heading by origin point
	@param radian the angle descriped by radian
	*/
	void rotate(float radian)
	{
		_heading.rotateByAngle(Vec2::ZERO, radian);
	}

	/*是否和矩形（任意角度）相交
	@param other 判断目标
	@param rv 斥力向量，作为引用参数返回
	@return 是否相交
	*/
	bool intersectRect(const SlantRect& other, Vec2& rv) const
	{
		auto selfQ = this->FourVertex();
		auto otherQ = other.FourVertex();

		//先检测aabb
		if (!selfQ.get_aabb_box().intersectsRect(otherQ.get_aabb_box()))
		{
			return false;
		}

		//再检测四个点

		//先转化到本地坐标系
		auto o_h_t_s_l = VectorToLocalSpace(other.heading(), _heading, _heading.getPerp());
		auto o_o_t_s_l = PointToLocalSpace(other.originRect().origin, _heading, _heading.getPerp(), _originRect.origin);
		auto otherOnLocal = SlantRect(Rect(o_o_t_s_l, other.originRect().size), o_h_t_s_l);

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
			auto s_h_t_o_l = VectorToLocalSpace(_heading, other.heading(), other.heading().getPerp());
			auto s_o_t_o_l = PointToLocalSpace(_originRect.origin, other.heading(), other.heading().getPerp(), other.originRect().origin);
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
				auto pivot = Vec2(other.originRect().size) / 2;

				auto selfPivot = (newSelfQ.a + newSelfQ.b + newSelfQ.c + newSelfQ.d) / 4;
				
				auto localRv = (rp - pivot).getNormalized()*pivot.getDistance(selfPivot);

				rv = VectorToWorldSpace(localRv, other.heading(), other.heading().getPerp());

				return true;
			}
		}

		return false;
	}

	const Vec2 heading() const { return _heading; }

	const Rect originRect() const { return _originRect; }

	virtual Vec2 centroid() override
	{
		auto temp = FourVertex();

		return (temp.a + temp.b + temp.c + temp.d) / 4;
	}
protected:
	Quadrangle FourVertex() const
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
private:
	Rect _originRect;
	Vec2 _heading;
};


#endif
