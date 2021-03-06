#ifndef _COMMUNICATOR_H_
#define _COMMINICATOR_H_
#include "Telegram.h"
#include "ObjectBase.h"
#include "ComponentBase.h"
#include "MsgDispatcher.h"
#include <functional>

class CompCommunicator:public ComponentBase
{
public:
	function<bool(const Telegram&)> handleMsg;

	void sendMsg(long delay, int sender, int receiver, MsgType type, void* extra = nullptr)
	{
		MSGDISPATCHER->addMsg(delay, sender, receiver, type, extra);
	}

	virtual bool init()override 
	{ 
		if (!root)
			return false;
		return true; 
	}

	virtual void update() override {}

	virtual void clear() override {}
};

#endif // !_COMMUNICATOR_H_

