#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "cocos2d.h"
#include "Tranformation.h"
#include "CommonUtils.h"
#include <numeric>
#include "CollisionVolume.h"

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

class Circle;

class SlantRect: public CollisionVolume
{
#pragma region ctors & cloner
public:
	SlantRect(const Rect& origin, const Vec2& heading);

	~SlantRect() = default;

	SlantRect(const SlantRect& other);

	SlantRect cloneTo(const Vec2 origin) const;

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

	virtual CollisionVolume* realCV(const Vec2& pos, const Vec2& heading) override;

	virtual bool intersects(CollisionVolume* other, Vec2& repulsion) override;

	/*rotate the heading by origin point
	@param radian the angle descriped by radian
	*/
	void rotate(float radian);

	/*是否和矩形（任意角度）相交
	@param other 判断目标
	@param rv 斥力向量，作为引用参数返回
	@return 是否相交
	*/
	bool intersectRect(SlantRect* other, Vec2& rv) const;

	bool intersectCircle(Circle* other, Vec2 rv) const;

	const Vec2 heading() const { return _heading; }

	const Rect originRect() const { return _originRect; }

	virtual Vec2 centroid() override;
protected:
	Quadrangle FourVertex() const;
private:
	Rect _originRect;
	Vec2 _heading;
};


#endif
