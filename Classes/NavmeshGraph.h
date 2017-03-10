#ifndef _NEVMESH_GRAPH_H_
#define _NEVMESH_GRAPH_H_

#include "ConvexPolygon.h"
#include <unordered_map>

namespace recast_navigation {

	typedef int PolyRef;

	typedef struct {
		ConvexPolygon polygon;
		PolyRef idx;
	}GraphNode, *GraphNodePtr;

	class NavmeshGraph
	{
	public:
		NavmeshGraph();

		// open filename.navmesh to load data
		virtual bool loadFromFile(const string& filename);
	private:
		std::unordered_map<PolyRef, GraphNode> _nodeMap;

	};
}


#endif
