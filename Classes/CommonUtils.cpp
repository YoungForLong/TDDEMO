#include "CommonUtils.h"

float CommonUtils::transformHeadingToRotation(const Vec2 & heading)
{
	return 90 - heading.getAngle() * 180 / PI;
}

Value CommonUtils::getConfigByKey(ObjectType type,const std::string & key)
{
	auto thisTypeConfig = _config[type];
	
	return thisTypeConfig[key];
}
