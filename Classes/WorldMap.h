#ifndef _WORLD_MAP_H_
#define _WORLD_MAP_H_

#include "Singleton.h"
#include "Lib_Navmesh\AStarSearch.h"

using namespace recast_navigation;

class WorldMap :public Singleton<WorldMap>
{
public:
	~WorldMap();

	void init();
	vector<Vec2> getPath(const Vec2& start, const Vec2& end);
private:
	NavmeshGraph* _nvmgh;
	AStarSearch* _pathFinder;

	const float scaleFactor = 0.1f;
};

#endif