#ifndef _CONVEX_POLYGON_H_
#define _CONVEX_POLYGON_H

#include "cocos2d.h"
#include <unordered_set>

using namespace std;
using namespace cocos2d;


namespace recast_navigation {

	struct Triangle
	{
		Vec2 vertexes[3];

		Vec2 centroid()
		{
			Vec2 sum = Vec2::ZERO;
			for (int i = 0; i < 3; ++i)
			{
				sum += vertexes[i];
			}

			return sum / 3.0f;
		}

		float area()
		{
			float x1 = vertexes[0].x;
			float y1 = vertexes[0].y;
			float x2 = vertexes[1].x;
			float y2 = vertexes[1].y;
			float x3 = vertexes[2].x;
			float y3 = vertexes[2].y;

			return (x1*y2 + y1*x3 + y1*x2*y3 - x3*y3 - x1*y3 - x2*y1);
		}
	};

	// none cloner
	// counter-clock-wise points
	class ConvexPolygon
	{
	public:
		ConvexPolygon(Vec2 arg, ...);

		ConvexPolygon(const initializer_list<Vec2>& argList);

		ConvexPolygon(const vector<Vec2>& arr);

		std::vector<Vec2> vertexArr;

		Vec2 centroid;

		// divide poly into triangles
		std::vector<Triangle> divide();

		bool containsPoint(const Vec2& p) const;

	protected:
		// ºÏ≤‚∆‰∞ºÕπ–‘
		bool checkConvex();

		// @return cos(A)
		float tri_point_to_angle(const Vec2& p1,const Vec2& p2,const Vec2& p3);

		void calculateCentroid();
	};
}


#endif
