#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "ReferNode.h"
#include <set>
#include <algorithm>

namespace recast_navigation {
	
	class Vertex:public ReferNode
	{
	public:
		Vertex(std::map<int, ReferNode*>& refmap):
			ReferNode(refmap)
		{}

		void attach(VertexRef another);
	private:
		std::set<Edge> _edges;
	};

}

#endif