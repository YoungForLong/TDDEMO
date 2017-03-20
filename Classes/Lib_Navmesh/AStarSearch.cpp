#include "AStarSearch.h"


recast_navigation::AStarSearch::AStarSearch(NavmeshGraph& source):
	_sourceMap(source),
	_route(source.size() + 1,0)// 0��λ����
{
}

recast_navigation::AStarSearch::~AStarSearch()
{
}

vector<int> recast_navigation::AStarSearch::result(const Vec2 & start, const Vec2 & end)
{
	_start = start;
	_end = end;
	search();

	stack<int> path;
	int parent = _endNode;
	path.push(parent);
	while (parent != _startNode)
	{
		parent = _route[parent];
		path.push(parent);
	}

	// �����л�
	vector<int> ret;

	while (!path.empty())
	{
		int idx = path.top();
		CCLOG("path node: %d", idx);
		path.pop();

		ret.push_back(idx);
	}

	return ret;
}

vector<Vec2> recast_navigation::AStarSearch::path(const Vec2 & start, const Vec2 & end)
{
	auto nodes = result(start, end);
	
	//·���Ĺյ�
	vector<Vec2> ret;
	ret.push_back(start);

	int length = nodes.size();
	int count = 1;
	while (ret.back().distanceSquared(end) > 1 && count < length)//ֱ��Ѱ�ҵ�·���㣬����Ϊ1
	{
		Edge e = _sourceMap.getNodeById(nodes[count])
			->poly.findCommonEdge(_sourceMap.getNodeById(nodes[count - 1])->poly);

		Vec2 curPoint = ret.back();
		

		count++;
	}

	return ret;
}

vector<Vec2> recast_navigation::AStarSearch::LOS_path(const Vec2 & start, const Vec2 & end)
{
	auto nodes = result(start, end);

	//�ҵ����й�����
	vector<Edge> allCommonEdges;
	for (int i = 1; i < nodes.size(); ++i)
	{
		auto poly1 = _sourceMap.getNodeById(nodes[i - 1])->poly;
		auto poly2 = _sourceMap.getNodeById(nodes[i])->poly;
		allCommonEdges.push_back(poly1.findCommonEdge(poly2));
	}

	vector<Vec2> ret;
	ret.push_back(start);
	
	for (int i = 0; i < allCommonEdges.size(); ++i)
	{
		//��������
		Vec2 n = end - ret.back();

		auto tempE = allCommonEdges[i];
		if (tempE.containsPoint(ret.back()))
			continue;

		if (NavmeshGraph::LOS_test(n, tempE))
		{
			Vec2 tunrningPoint = (tempE.from.distanceSquared(end) < tempE.to.distanceSquared(end)) ? tempE.from : tempE.to;
			ret.push_back(tunrningPoint);
		}
	}

	ret.push_back(end);

	return ret;
}

bool recast_navigation::AStarSearch::search()
{
	// ����δ���������У����Ѿ������ʹ��Ľڵ�
	priority_queue<GraphNode*,vector<GraphNode*>,cmp> OPEN;

	// map��id��1��ʼ
	const int mapSize = _sourceMap.size() + 1;

	// �Ƿ��Ѿ��������ҷ�������
	vector<bool> CLOSE(mapSize, false);
	
	// �Ƿ���OPEN����
	vector<bool> isInOpen(mapSize, false);

	// Դ�ڵ����
	int startId = _sourceMap.pointInWhichPoly(_start);
	_startNode = startId;
	OPEN.push(_sourceMap.getNodeById(startId));
	isInOpen.at(startId) = true;
	//_FValueArr.at(startId) = 0.0f;

	while (!OPEN.empty())
	{
		//Fֵ��С�ĳ�����
		auto curNode = OPEN.top();
		OPEN.pop();
		CLOSE.at(curNode->idx) = true;//���г����еĽڵ㣬���ΪCLOSE
		isInOpen.at(curNode->idx) = false;

		//�ҵ�Ŀ��ڵ㣬�˳�ѭ��
		if (curNode->poly.containsPoint(_end))
		{
			_endNode = curNode->idx;
			return true;
		}
		
		//�����ڽڵ�ȫ����ӣ�ǰ���ǲ���OPEN���У�����CLOSE���У�δ��������
		for (int i = 0; i < curNode->siblings.size(); ++i)
		{
			auto next = _sourceMap.getNodeById(curNode->siblings.at(i));

			if (CLOSE[next->idx])
				continue;

			if (isInOpen[next->idx] == false)
			{
				// ����·�����ĸ��ڵ�id
				_route[next->idx] = curNode->idx;
				
				// ���¼���FValue
				next->FValue = F_func(curNode, next);
				next->FValue += curNode->FValue;

				// ����OPEN��
				OPEN.push(next);
				isInOpen.at(next->idx) = true;
			}
			else // �����OPEN���У���Ҫ���¼��㣬�Ƚ�����һ�����ڵ����С������������ڵ��������С
			{
				float curFValue = next->FValue;
				float newFValue = F_func(curNode, next);
				
				if (newFValue < curFValue)
				{
					// �������ڵ��FValue
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
