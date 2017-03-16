#ifndef _NEVMESH_GRAPH_H_
#define _NEVMESH_GRAPH_H_

#include "ConvexPolygon.h"
#include <unordered_map>

namespace recast_navigation {
	enum PolyType
	{
		obstacle,
		sea
	};

	typedef Vec2 Edge[2];

	struct GraphNode{
		int idx;
		ConvexPolygon poly;
		vector<int> siblings;
		PolyType type;
		float FValue;//被外部随时更新

		GraphNode(int index,const ConvexPolygon& polygon, PolyType t,int arg, ...):
			idx(index),
			poly(polygon),
			type(t)
		{
			va_list argArr;
			int temp = 1;

			va_start(argArr, arg);

			while (temp)
			{
				temp = va_arg(argArr, int);

				siblings.push_back(temp);
			}

			va_end(argArr);

		}

		void operator= (const GraphNode& other)
		{
			idx = other.idx;
			poly = other.poly;
			siblings = other.siblings;
		}
	};

	class NavmeshGraph
	{
	public:
		NavmeshGraph();

		// open filename.navmesh to load data
		virtual bool loadFromFile(const string& filename);

		
		vector<Vec2> AStarSearch(Vec2 start, Vec2 end);

		int pointInWhichPoly(const Vec2& point);

		/**
		* LOS_test a test of whether the edge is intersect to a vector
		* @param heading the vector agent is heading to
		* @param e the edge
		* @return false means intersection, on the contrary true means none
		*/
		static bool LOS_test(const Vec2 heading, Edge e);

		const int size()const { return _size; }

		GraphNode* getNodeById(int id) const { return _nodeMap.at(id); }

	public:// dynamic change the map during runtime
		void addPoly(GraphNode* node);
		void sliceEdge(Vec2 from, Vec2 to);
		void combineEdge(Vec2 from, Vec2 to);
	private:
		std::unordered_map<int, GraphNode*> _nodeMap;
		int _size;
	};
}


#endif
