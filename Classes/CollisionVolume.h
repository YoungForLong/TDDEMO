#ifndef _COLLISION_VOLUME_H_
#define _COLLISION_VOLUME_H_
#include"cocos2d.h"
#include"Circle.h"

using namespace cocos2d;
//碰撞体积结构体,由圆形和方形或小方格拼接

enum centreAlign
{
	mid_mid,//正中心
	mid_bottom,//底部中心
	left_bottom//左下角
};
class CollisionVolume
{
public:
	//此处的位置都是指相对于锚点的位置
	std::vector<Rect> rect_;
	std::vector<Circle> circle_;
	float totalWidth_;
	float totalHeight_;
	bool containsPoint(Point);
	bool intersectsCV(CollisionVolume);
	centreAlign anchorPoint_;//锚点
};

#endif