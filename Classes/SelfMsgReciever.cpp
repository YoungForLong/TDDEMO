#include "SelfMsgReciever.h"
#include "ComponentDependencies.h"

bool SelfMsgReciever::init()
{
	if(!EntityBase::init())
		return false;

	//定义消息处理
	auto compCommunicator = this->addComponent<CompCommunicator>(comp_communicator);
	compCommunicator->handleMsg = [](const Telegram& msg)->bool {
		if (msg.msg_ == msg_destroy_self)
		{
			auto entity = OMGR->getEntityById(msg.sender_);
			OMGR->removeEntity(entity);
			return true;
		}

		return false;
	};

	return true;
}

SelfMsgReciever * SelfMsgReciever::create()
{
	auto ret = new SelfMsgReciever(selfMsgReceiver_id);
	if (ret->init())
	{
		OMGR->registerEntity(ret);
		return ret;
	}
	else
		return nullptr;
}
