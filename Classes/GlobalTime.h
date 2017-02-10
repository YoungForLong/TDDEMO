#ifndef _GLOBAL_TIME_H_
#define _GLOBAL_TIME_H_

#include "Singleton.h"

class GlobalTime :public Singleton<GlobalTime>
{
public:
	/*在程序运行的开头运行，初始化计时器
	*/
	void init();

	/*在每帧的开头执行
	*/
	void update();

public://properties

	long deltaTime;//和上一帧的时间差，单位ms

	long totalTime;//当前帧的时间，单位ms

	long startTime;//应用程序开始时间
};

#define GT GlobalTime::instance()

#endif
