#ifndef _COLLISION_VOLUME_H_
#define _COLLISION_VOLUME_H_

#include "cocos2d.h";

USING_NS_CC;

enum CVType
{
	circle,
	slant_rect
};

class CollisionVolume
{
public:
	CVType type_;

	//根据物体实际地址计算新的碰撞体积
	virtual CollisionVolume* realCV(const Vec2& pos, const Vec2& heading) = 0;

	//质心
	virtual Vec2 centroid() = 0;

	/*是否和另一个CV发生碰撞
	@param other 碰撞体
	@param repulsion 斥力
	*/
	virtual bool intersects(CollisionVolume* other, Vec2& repulsion) = 0;
};


#endif //! collision volume
