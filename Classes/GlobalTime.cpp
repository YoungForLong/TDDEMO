#include "GlobalTime.h"
#include "cocos2d.h"

using namespace cocos2d;

void GlobalTime::init()
{
	timeval tv;
	gettimeofday(&tv, NULL);

	startTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	totalTime = 0;

	deltaTime = 0;
}

void GlobalTime::update()
{
	timeval tv;
	gettimeofday(&tv, NULL);

	auto curTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	auto lastTotalTime = totalTime;
	totalTime = curTime - startTime;

	deltaTime = totalTime - lastTotalTime;
}
