#include "CommonUtils.h"

float CommonUtils::transformHeadingToRotation(const Vec2 & heading)
{
	return 90 - heading.getAngle() * 180 / PI;
}
