#include "AStarSearch.h"


recast_navigation::AStarSearch::AStarSearch(NavmeshGraph& source):
	_sourceMap(source),
	_FValueArr(source.size(),infinity_float),
	_route(source.size(),0)
{
}

recast_navigation::AStarSearch::~AStarSearch()
{
}

vector<int> recast_navigation::AStarSearch::result(const Vec2 & start, const Vec2 & end)
{
	return vector<int>();
}

bool recast_navigation::AStarSearch::search()
{
	// 储存未被存入树中，但已经被访问过的节点
	priority_queue<GraphNode*,vector<GraphNode*>,cmp> OPEN;

	// map的id从1开始
	const int mapSize = _sourceMap.size() + 1;

	// 是否已经被访问且放入树中
	vector<bool> CLOSE(mapSize, false);
	
	// 是否还在OPEN表中
	vector<bool> isInOpen(mapSize, false);

	// 源节点入队
	int startId = _sourceMap.pointInWhichPoly(_start);
	OPEN.push(_sourceMap.getNodeById(startId));
	isInOpen.at(startId) = true;
	_FValueArr.at(startId) = 0.0f;

	while (!OPEN.empty())
	{
		//F值最小的出队列
		auto curNode = OPEN.top();
		OPEN.pop();
		CLOSE.at(curNode->idx) = true;//所有出队列的节点，标记为CLOSE
		isInOpen.at(curNode->idx) = false;

		//找到目标节点，退出循环
		if (curNode->poly.containsPoint(_end))
		{
			return true;
		}
		
		//把相邻节点全部入队，前提是不在OPEN表中，不在CLOSE表中（未加入树）
		for (int i = 0; i < curNode->siblings.size(); ++i)
		{
			auto next = _sourceMap.getNodeById(curNode->siblings.at(i));

			if (CLOSE[next->idx])
				continue;

			if (isInOpen[next->idx] == false)
			{
				//储存路径树的父节点id
				_route[next->idx] = curNode->idx;
				
				//重新计算FValue
				next->FValue = F_func(curNode, next);
				next->FValue += curNode->FValue;

				//更新OPEN表
				OPEN.push(next);
				isInOpen.at(next->idx) = true;
			}
			else // 如果在OPEN表中，需要重新计算，比较是上一个父节点迭加小还是现在这个节点迭加起来小
			{
				float curFValue = next->FValue;
				float newFValue = F_func(curNode, next);
				
				if (newFValue < curFValue)
				{
					//更换父节点和FValue
					_route[next->idx] = curNode->idx;
					next->FValue = newFValue;
				}
			}
		}// end for

	}// end while

	return false;
}

float recast_navigation::AStarSearch::F_func(const GraphNode* last,const GraphNode* cur)
{
	return H_func(last->poly.centroid, cur->poly.centroid)
		+ G_func(cur->poly.centroid);
}

float recast_navigation::AStarSearch::H_func(const Vec2 & last, const Vec2 & cur)
{
	return last.distanceSquared(cur);
}

float recast_navigation::AStarSearch::G_func(const Vec2 & centroid)
{
	return centroid.distanceSquared(_end);
}
