#include "ConvexPolygon.h"

using namespace recast_navigation;

recast_navigation::ConvexPolygon::ConvexPolygon(Vec2 arg, ...)
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

	if (!checkConvex())
	{
		vertexSet.clear();
		assert(0 &&
			"it's not a convex poly");
	}

	calculateCentroid();
}

recast_navigation::ConvexPolygon::ConvexPolygon(const initializer_list<Vec2>& argList)
{
	for (auto iter = argList.begin(); iter != argList.end; ++iter)
	{
		vertexSet.insert(*iter);
	}

	if (!checkConvex())
	{
		vertexSet.clear();
		assert(0 &&
			"it's not a convex poly");
	}

	calculateCentroid();
}

recast_navigation::ConvexPolygon::ConvexPolygon(const ConvexPolygon & other)
{
	vertexSet.clear();

	for (auto iter = other.vertexSet.cbegin(); iter != other.vertexSet.cend(); ++iter)
	{
		vertexSet.insert(*iter);
	}
}

std::vector<Triangle> recast_navigation::ConvexPolygon::divide()
{
	vector<Triangle> ret;

	auto iter = vertexSet.cbegin();
	const Vec2 first_vertex = *iter;
	
	// turn to the next
	iter++;

	while (true)
	{
		Triangle temp;
		temp.vertexes[0] = first_vertex;
		temp.vertexes[1] = *(iter++);

		if (iter == vertexSet.cend())
			break;
		temp.vertexes[2] = *iter;

		ret.push_back(temp);
	}

	return ret;
}

bool recast_navigation::ConvexPolygon::containsPoint(const Vec2 & p)
{
	auto iter = vertexSet.cbegin();
	auto second = ++vertexSet.cbegin();
	auto end = vertexSet.cend();

	Vec3 lastTest = Vec3::ZERO;
	while (iter != end)
	{
		Vec2 beginPoint = *iter;
		Vec2 endPoint = *(++iter);

		Vec2 e2d = endPoint - beginPoint;
		Vec2 t2d = p - beginPoint;

		Vec3 e3d = Vec3(e2d.x, e2d.y, 0);
		Vec3 t3d = Vec3(t2d.x, t3d.y, 0);

		Vec3 curTest;
		Vec3::cross(e3d, t3d, &curTest);

		//第一次检测
		if (iter == second)
		{
			lastTest = curTest;
			continue;
		}

		bool tag1 = lastTest.z > 0;
		bool tag2 = curTest.z > 0;

		if (tag1 == tag2)
		{
			lastTest = curTest;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool recast_navigation::ConvexPolygon::checkConvex()
{
	if (vertexSet.size() < 3)
		return false;

	auto beginIter = vertexSet.begin();
	auto endIter = vertexSet.end();
	auto iter = vertexSet.begin();

	//第一组点
	auto temp = iter;
	auto p1 = *(iter++);
	auto p2 = *(iter++);
	auto p3 = *iter;
	float last_cos_angle = tri_point_to_angle(p1, p2, p3);
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
		float cos_angle_124 = tri_point_to_angle(pArr[0], pArr[1], pArr[3]);

		// cos单调递减
		if (last_cos_angle > cos_angle_124)
			return false;

		// angle 234
		last_cos_angle = tri_point_to_angle(pArr[1], pArr[2], pArr[3]);

		iter = ++temp;
	}

	return true;
}

float recast_navigation::ConvexPolygon::tri_point_to_angle(const Vec2 & p1, const Vec2 & p2, const Vec2 & p3)
{
	Vec2 v1 = p1 - p2;
	Vec2 v2 = p3 - p2;

	float cos_angle = v1.cross(v2) / (v1.length*v2.length);

	return cos_angle;
}

void recast_navigation::ConvexPolygon::calculateCentroid()
{
	// 质心等于分解质心的加权平均

	Vec2 sumWeight = Vec2::ZERO;
	float sumA = 0.0f;

	auto tris = this->divide();

	for (auto iter = tris.begin(); iter != tris.end(); ++iter)
	{
		Vec2 eachC = (*iter).centroid();
		float eachArea = (*iter).area();

		sumA += eachArea;
		sumWeight += eachC*eachArea;
	}

	centroid = sumWeight / sumA;
}

