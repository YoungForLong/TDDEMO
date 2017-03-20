#ifndef _A_STAR_SEARCH_H_
#define _A_STAR_SEARCH_H_

#include "NavmeshGraph.h"

namespace recast_navigation {

	const float infinity_float = 3.402823466e+38F;

	//functor
	struct cmp {
		bool operator()(GraphNode* one, GraphNode* another)
		{
			return one->FValue > another->FValue;
		}
	};

	class AStarSearch
	{
	public:
		AStarSearch(NavmeshGraph& source);
		~AStarSearch();

		vector<int> result(const Vec2& start, const Vec2& end);

		// 拐角点法求路径
		vector<Vec2> path(const Vec2& start, const Vec2& end);

		// 光照射线法求路径
		vector<Vec2> LOS_path(const Vec2& start, const Vec2& end);
	protected:
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
		
		// 存放搜索路径的初始节点和目的节点，避免重复计算
		int _startNode;
		int _endNode;

		NavmeshGraph& _sourceMap;
		vector<int> _route; // 存放的是最短路径生成树的所有叶子的父节点
	};
}

#endif
