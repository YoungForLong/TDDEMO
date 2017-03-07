#ifndef _REFER_NODE_H_
#define _REFER_NODE_H_

#include <map>

// 通过索引访问的节点

namespace recast_navigation {

	typedef int VertexRef;
	typedef int EdgeRef;
	typedef int PolyRef;

	class ReferNode
	{
	public:
		
		ReferNode(std::map<int, ReferNode*>& refmap):
			_refMap(refmap)
		{}

		bool operator >(const ReferNode& other)
		{
			return index > other.index;
		}

		ReferNode& Data()
		{
			return *(_refMap[index]);
		}

		int index;

	private:
		std::map<int, ReferNode*>& _refMap;
	};
}

#endif // !_REFER_NODE_H_
