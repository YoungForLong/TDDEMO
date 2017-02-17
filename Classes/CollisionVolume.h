#ifndef _COLLISION_VOLUME_H_
#define _COLLISION_VOLUME_H_
#include"cocos2d.h"
#include"Circle.h"

using namespace cocos2d;
//��ײ����ṹ��,��Բ�κͷ��λ�С����ƴ��

enum centreAlign
{
	mid_mid,//������
	mid_bottom,//�ײ�����
	left_bottom//���½�
};
class CollisionVolume
{
public:
	//�˴���λ�ö���ָ�����ê���λ��
	std::vector<Rect> rect_;
	std::vector<Circle> circle_;
	float totalWidth_;
	float totalHeight_;
	bool containsPoint(Point);
	bool intersectsCV(CollisionVolume);
	centreAlign anchorPoint_;//ê��
};

#endif