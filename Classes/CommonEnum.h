#ifndef _COMMON_ENUM_H_
#define _COMMON_ENUM_H_

#include <map>
#include "cocos2d.h"

enum MsgType 
{
	msg_destroy_self,
};

enum ObjectType 
{
	bullet,
	stone_bullet,
};

enum ComponentType
{
	comp_null_type = 0x0000,
	comp_communicator = 0x0001,
	comp_moving = 0x0002,
	comp_displayer = 0x0004
};

enum AttackBonus
{
	//普攻
	normal	= 0x0001,
	//暴击
	crit	= 0x0002,
	//减速
	slow	= 0x0004,
	//晕眩
	stun	= 0x0008,
	//持续伤害
	dot		= 0x0016
	//to do, more types
};

//math
#define PI 3.1415926
const float max_float = 99999;

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
const float ObsAvoiWeight = 10.0f;
const float PursuitWeight = 1.0f;
const float EvadeWeight = 1.0f;
const size_t smoothing_frames = 10;

//id，从1-100为系统保留id
const int illegal_id = -9999;
const int selfMsgReceiver_id = 1;

//depth,z_order
const int bg_zorder = -10;

#define CREATE_SPRITE(__filename__) (Sprite::create(__filename__))

#endif
