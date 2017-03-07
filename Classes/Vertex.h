#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "ReferNode.h"
#include <vector>

namespace recast_navigation {
	
	class Vertex:public ReferNode
	{
	public:
		Vertex(std::map<int, ReferNode*>& refmap):
			ReferNode(refmap)
		{}

		bool addEdge(EdgeRef er);
	private:
		std::vector<EdgeRef> _edges;
	};

}

#endif