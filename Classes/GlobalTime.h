#ifndef _GLOBAL_TIME_H_
#define _GLOBAL_TIME_H_

#include "Singleton.h"

class GlobalTime :public Singleton<GlobalTime>
{
public:
	/*�ڳ������еĿ�ͷ���У���ʼ����ʱ��
	*/
	void init();

	/*��ÿ֡�Ŀ�ͷִ��
	*/
	void update();

public://properties

	long deltaTime;//����һ֡��ʱ����λms

	long totalTime;//��ǰ֡��ʱ�䣬��λms

	long startTime;//Ӧ�ó���ʼʱ��
};

#define GT GlobalTime::instance()

#endif
