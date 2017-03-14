#include "NavmeshGraph.h"
#include <map>
#include <queue>

recast_navigation::NavmeshGraph::NavmeshGraph()
{
}

bool recast_navigation::NavmeshGraph::loadFromFile(const string & filename)
{
	return false;
}

vector<Vec2> recast_navigation::NavmeshGraph::AStarSearch(Vec2 start, Vec2 end)
{
	
}

int recast_navigation::NavmeshGraph::pointInWhichPoly(const Vec2 & point)
{
	for (auto iter = _nodeMap.begin(); iter != _nodeMap.end(); ++iter)
	{
		auto node = (*iter).second;
		auto poly = node->poly;

		if (poly.containsPoint(point))
		{
			return node->idx;
		}
	}

	CCLOG("cannot find this point in map, point£º %f, %f", point.x, point.y);
	return 0;
}

bool recast_navigation::NavmeshGraph::LOS_test(const Vec2 heading, Edge e)
{
	Vec3 h3d = Vec3(heading.x, heading.y, 0);
	Vec3 f3d = Vec3(e[0].x, e[0].y, 0);
	Vec3 t3d = Vec3(e[1].x, e[1].y, 0);

	Vec3 test_a = Vec3::ZERO;
	Vec3 test_b = Vec3::ZERO;
	
	Vec3::cross(f3d, h3d, &test_a);
	Vec3::cross(t3d, h3d, &test_b);

	bool tag_a = test_a.z > 0;
	bool tag_b = test_b.z > 0;

	return tag_a == tag_b;
}

void recast_navigation::NavmeshGraph::addPoly(GraphNode* node)
{
	_nodeMap.insert(make_pair(node->idx,node));
}

void recast_navigation::NavmeshGraph::sliceEdge(Vec2 from, Vec2 to)
{
}

void recast_navigation::NavmeshGraph::combineEdge(Vec2 from, Vec2 to)
{
}
