#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_
#include "Singleton.h"
#include "cocos2d.h"
#include "CommonEnum.h"

using namespace cocos2d;

class CommonUtils :public Singleton<CommonUtils>
{
public:
	std::map<ObjectType,std::map<std::string, Value>> _config;

	bool A_is_belong_to_B(string A, string B);

	float transformHeadingToRotation(const Vec2& heading);

	void loadConfig();

	Value getConfigByKey(ObjectType type,const std::string& key);
};

#define CU CommonUtils::instance()

#endif // ! _COMMON_UTILS_H_
