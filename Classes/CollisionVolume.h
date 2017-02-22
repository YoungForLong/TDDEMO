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

	//��������ʵ�ʵ�ַ�����µ���ײ���
	virtual CollisionVolume* realCV(const Vec2& pos, const Vec2& heading) = 0;

	//����
	virtual Vec2 centroid() = 0;

	/*�Ƿ����һ��CV������ײ
	@param other ��ײ��
	@param repulsion ����
	*/
	virtual bool intersects(CollisionVolume* other, Vec2& repulsion) = 0;
};


#endif //! collision volume
