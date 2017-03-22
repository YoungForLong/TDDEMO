#ifndef _MSG_DISPATCHER_H_
#define _MSG_DISPATCHER_H_

#pragma warning(disable 4768)
#include<set>
#include<assert.h>
#include<algorithm>
#include<functional>
#include<time.h>
#include"Singleton.h"
#include"Telegram.h"

class CompCommunicator;

class MsgDispatcher :public Singleton<MsgDispatcher>
{
private:
	std::set<Telegram> _msgQueue;//ordered by dispatchTime
protected:
	void discharge(CompCommunicator*, const Telegram&);
public:
	MsgDispatcher(){}
public:
#define DEFAULT_DELAY 0.0f 

#define NO_EXTRA_INFO NULL

public:
	void addMsg(long int tiemdelay, int sender, int receiver, MsgType msg, void* extra);
public:
	void update() { dispatchMsg(); }

	//updated func
	void dispatchMsg();
};


#define MSGDISPATCHER MsgDispatcher::instance()


#endif