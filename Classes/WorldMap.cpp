#include "WorldMap.h"

WorldMap::~WorldMap()
{
	if (_nvmgh)
	{
		delete _nvmgh;
		_nvmgh = nullptr;
	}

	if (_pathFinder)
	{
		delete _pathFinder;
		_pathFinder = nullptr;
	}
}

void WorldMap::init()
{
	_nvmgh = new NavmeshGraph();
	_nvmgh->loadFromFile("navmesh.json");

	_pathFinder = new AStarSearch(*_nvmgh);
}

vector<Vec2> WorldMap::getPath(const Vec2 & start, const Vec2 & end)
{
	auto ret = _pathFinder->tp_path(start*scaleFactor, end*scaleFactor);

	for (auto iter = ret.begin(); iter != ret.end(); ++iter)
	{
		*iter = (*iter) / scaleFactor;
	}

	return ret;
}
