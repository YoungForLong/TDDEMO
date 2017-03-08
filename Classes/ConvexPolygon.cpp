#include "ConvexPolygon.h"

bool recast_navigation::ConvexPolygon::set(Vec2 arg, ...)
{
	va_list argArr;

	Vec2 temp = arg;

	va_start(argArr, arg);

	while (temp != nullptr)
	{
		temp = va_arg(argArr, Vec2);
		vertexSet.insert(temp);
	}
	
	va_end(argArr);

	if (checkConvex())
	{
		return true;
	}
	else
	{
		vertexSet.clear();
		return false;
	}
}

bool recast_navigation::ConvexPolygon::checkConvex()
{
	auto beginIter = vertexSet.begin();
	auto endIter = vertexSet.end();
	auto iter = vertexSet.begin();

	//第一组点
	auto temp = iter;
	auto p1 = *(iter++);
	auto p2 = *(iter++);
	auto p3 = *iter;
	float last_cos_angle = tri_point_angle(p1, p2, p3);
	iter = temp;

	while (true)
	{
		if (iter == vertexSet.begin())
			break;

		auto temp = iter;
		
		Vec2 pArr[4];
		pArr[0] = *iter;
		for (int i = 1; i < 4; ++i)
		{
			iter++;
			iter = iter == endIter ? beginIter : iter;
			pArr[i] = *iter;
		}

		// angle 124
		float cos_angle_124 = tri_point_angle(pArr[0], pArr[1], pArr[3]);

		// cos单调递减
		if (last_cos_angle > cos_angle_124)
			return false;

		// angle 234
		last_cos_angle = tri_point_angle(pArr[1], pArr[2], pArr[3]);

		iter = ++temp;
	}

	return true;
}

float recast_navigation::ConvexPolygon::tri_point_angle(const Vec2 & p1, const Vec2 & p2, const Vec2 & p3)
{
	Vec2 v1 = p1 - p2;
	Vec2 v2 = p3 - p2;

	float cos_angle = v1.cross(v2) / (v1.length*v2.length);

	return cos_angle;
}

