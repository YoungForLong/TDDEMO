#ifndef _COMP_CONTROLLER_TEST_H_
#define _COMP_CONTROLLER_TEST_H_

//�ṩtest�ļ��Ĳ�����������Ҫ���ս��ģ��
//a bref test example for battle module
#include "ComponentBase.h"

class CompControllerTest:public ComponentBase
{
public:
	virtual bool init() override;
	virtual void update() override;
	virtual void clear() override;
public://dealing with input
	void onKeyboardPressed(cocos2d::EventKeyboard::KeyCode code);
	void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode code);
protected:
	bool attack();
private:
	int _curKeyState;
};

#endif
