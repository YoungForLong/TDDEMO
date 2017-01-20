#ifndef _COMMON_ENUM_H_
#define _COMMON_ENUM_H_

#include <map>

enum MsgType 
{

};

enum ObjectType 
{

};

enum ComponentType
{
	null_type = 0x0000,
	communicator = 0x0001
};

const float FPS = 60.0f;
const int WHOLE_MAP_WIDTH = 10000;
const int WHOLE_MAP_HEIGHT = 10000;
const float ADT = 1.0f / FPS;

#endif
