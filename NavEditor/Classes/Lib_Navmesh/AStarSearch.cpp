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
	OPEN.push(_sourceMap.getNodeById(startId));
	isInOpen.at(startId) = true;
	_FValueArr.at(startId) = 0.0f;

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
				//����·�����ĸ��ڵ�id
				_route[next->idx] = curNode->idx;
				
				//���¼���FValue
				next->FValue = F_func(curNode, next);
				next->FValue += curNode->FValue;

				//����OPEN��
				OPEN.push(next);
				isInOpen.at(next->idx) = true;
			}
			else // �����OPEN���У���Ҫ���¼��㣬�Ƚ�����һ�����ڵ����С������������ڵ��������С
			{
				float curFValue = next->FValue;
				float newFValue = F_func(curNode, next);
				
				if (newFValue < curFValue)
				{
					//�������ڵ��FValue
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
