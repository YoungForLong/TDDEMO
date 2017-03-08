#ifndef _CONVEX_POLYGON_H_
#define _CONVEX_POLYGON_H

#include "cocos2d.h"
#include <unordered_set>

using namespace std;
using namespace cocos2d;

namespace recast_navigation {

	// none cloner
	// counter-clock-wise points 
	class ConvexPolygon
	{
	public:
		// counter-clock-wise
		bool set(Vec2 arg, ...);

		// ºÏ≤‚∆‰∞ºÕπ–‘
		bool checkConvex();

		// @return cos(A)
		static float tri_point_angle(const Vec2& p1,const Vec2& p2,const Vec2& p3);

		unordered_set<Vec2> vertexSet;
	};
}


#endif
