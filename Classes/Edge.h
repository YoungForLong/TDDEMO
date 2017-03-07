#ifndef _EDGE_H_
#define _EDGE_H_

#include "ReferNode.h"

namespace recast_navigation {

	// ÎÞÏò±ß
	class Edge :public ReferNode
	{
	public:
		Edge(std::map<int, ReferNode*>& ref) :
			ReferNode(ref)
		{}
	};

}


#endif // !_EDGE_H_

