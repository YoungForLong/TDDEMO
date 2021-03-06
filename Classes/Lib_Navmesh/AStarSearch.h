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

	// 优先级路径，访问越多的路径，优先级越高
	template<class T>
	struct PriorityPath
	{
		int priority;
		vector<T> path;

		// 为了排序方便，故意相反
		bool operator<(const PriorityPath<T>& other)
		{
			return priority > other.priority;
		}
	};

	class AStarSearch
	{
	public:
		AStarSearch(NavmeshGraph& source);
		~AStarSearch();

		vector<int> result(const Vec2& start, const Vec2& end);

		// 光照射线法求路径
		vector<Vec2> LOS_path(const Vec2& start, const Vec2& end);

		// turning point path, 拐点法求路径
		vector<Vec2> tp_path(const Vec2& start, const Vec2& end);

		/**
		* @return 0 means on target's left, 1 means right, 3 maens equal
		*/
		static int left_or_right(const Vec2& origin, const Vec2& target);

	protected:
		bool search();

		// 此处为了减少运算量，使用平方
		float F_func(const GraphNode* last, const GraphNode* cur);

		// H = dist(last, cur)
		float H_func(const Vec2& last, const Vec2& cur);
		
		// G = dist(centroid, end)
		float G_func(const Vec2& centroid);

		/**
		* @param ret ref param to output
		*/
		bool belongToPath(int start, int end, const vector<int>& oldPath, vector<int>& ret);
	private:
		Vec2 _start;
		Vec2 _end;
		
		// 存放搜索路径的初始节点和目的节点，避免重复计算
		int _startNode;
		int _endNode;

		NavmeshGraph& _sourceMap;
		vector<int> _route; // 存放的是最短路径生成树的所有叶子的父节点

		// 优化，每次寻路的结果我们都做保存，避免重复寻路
		list<PriorityPath<int>> _pathList;
		// 最多保存3个路径，根据最近的使用次数来排序
		const int maxCachePathNum = 3;
	};
}

#endif
