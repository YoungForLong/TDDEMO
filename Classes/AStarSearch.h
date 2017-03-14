#ifndef _A_STAR_SEARCH_H_
#define _A_STAR_SEARCH_H_

#include "NavmeshGraph.h"

namespace recast_navigation {

	const float infinity_float = 3.402823466e+38F;

	//functor
	struct cmp {
		bool operator()(const GraphNode& one, const GraphNode& another)
		{
			return one.FValue > another.FValue;
		}
	};

	class AStarSearch
	{
	public:
		AStarSearch(NavmeshGraph& source);
		~AStarSearch();

		vector<int> result(const Vec2& start, const Vec2& end);

		bool search();

		// 此处为了减少运算量，使用平方
		float F_func(const GraphNode* last, const GraphNode* cur);

		// H = dist(last, cur)
		float H_func(const Vec2& last, const Vec2& cur);
		
		// G = dist(centroid, end)
		float G_func(const Vec2& centroid);

	private:
		Vec2 _start;
		Vec2 _end;
		NavmeshGraph& _sourceMap;
		vector<float> _FValueArr;//存放的是节点的F value，如果还未计算，则存放的是infinity_float
		vector<int> _route;
	};
}

#endif
