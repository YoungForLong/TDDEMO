#ifndef _EDGE_H_
#define _EDGE_H_

#include "ReferNode.h"

namespace recast_navigation {

	// 无向边
	class Edge
	{
	public:
		Edge() {}

		Edge(const Edge& other)
		{

		}

		// 无向
		bool operator == (const Edge& other)
		{
			bool tagA = other.points[0] == this->points[0];
			bool tagB = other.points[1] == this->points[1];
			bool tagC = other.points[0] == this->points[1];
			bool tagD = other.points[1] == this->points[0];

			return (tagA && tagB) || (tagC && tagD);
		}

		VertexRef points[2];

	};

}


#endif // !_EDGE_H_

