#ifndef _COMMON_ENUM_H_
#define _COMMON_ENUM_H_

#include <map>
#include "cocos2d.h"

enum MsgType 
{
	msg_destroy_self,
	msg_reply_bullet_arrived,
	msg_on_attack,
};

enum ObjectType 
{
	bullet,
	stone_bullet,
	ship
};

enum ComponentType
{
	comp_null_type = 0x0000,
	comp_communicator = 0x0001,
	comp_moving = 0x0002,
	comp_displayer = 0x0004,
	comp_battle = 0x0008,
	comp_controller_test = 0x0016,
};

enum AttackBonus
{
	//�չ�
	normal	= 0x0001,
	//����
	crit	= 0x0002,
	//����
	slow	= 0x0004,
	//��ѣ
	stun	= 0x0008,
	//�����˺�
	dot		= 0x0016
	//to do, more types
};

//math
#define PI 3.1415926
const float max_float = 3.402823466e+38F;
const float precision = 0.001f;

//sys
const float FPS = 60.0f;
const float ADT = 1.0f / FPS;
const int next_frame = 1;

//map
const int WHOLE_MAP_WIDTH = 10000;
const int WHOLE_MAP_HEIGHT = 10000;
const cocos2d::Vec2 illegal_aim = cocos2d::Vec2(-999.0f, -999.0f);

//weight for force
const float BrakingWeight = 0.1f;
const float SeekWeight = 1.0f;
const float FleeWeight = 1.0f;
const float ObsAvoiWeight = 0.05f;
const float PursuitWeight = 1.0f;
const float EvadeWeight = 1.0f;
const size_t smoothing_frames = 20;
const float seek_offset_precision = 1.0f;

//id����1-100Ϊϵͳ����id
const int illegal_id = -9999;
const int selfMsgReceiver_id = 1;
const int hero_id = 2;

//depth,z_order
const int bg_zorder = -10;
//define [0,100) as world depth
const int world_below_sea_zorder = 0;
const int world_sea_zorder = 10;
const int world_above_sea_zorder = 20;
const int world_air_zorder = 30;

#define CREATE_SPRITE(__filename__) (Sprite::create(__filename__))

#endif
