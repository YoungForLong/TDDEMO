#pragma once
//一个空间划分器

#include <algorithm>
#include "cocos2d.h"
#include "Singleton.h"
#include "CommonEnum.h"

using namespace cocos2d;

class CompMoving;

struct Cell
{
	std::list<CompMoving*> members_;
	Rect box_;
	Cell(Rect new_box) :box_(new_box){}
};

class CellSpacePartition:public Singleton<CellSpacePartition>
{
private:
	//all cells
	std::vector<Cell> _cells;

	//world space 
	Rect _spaceRect;

	//cell nums
	int _cellNumX;
	int _cellNumY;

	//cell space
	double _cellSizeX;
	double _cellSizeY;

protected:
	int positionToIndex(const Vec2)const;

public:
	static const Rect map_size;
	static const int cell_number_x;
	static const int cell_number_y;

public:
	void init(Rect, int,int);
	void addEntity(CompMoving*);
	void updateEntity(CompMoving*, Vec2);
	std::vector<CompMoving*> getNeighbors(CompMoving*, double);
	void clear();
	const std::vector<Cell> getCells(Vec2, double);
	static CellSpacePartition* instance();
};

#define CSP CellSpacePartition::instance()

