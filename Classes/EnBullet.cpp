#include "EnBullet.h"
#include "ComponentDependencies.h"

bool EnBullet::init()
{
	//at begining
	if (!EntityBase::init())
		return false;

	this->addComponent<CompMoving>(comp_moving);
	this->addComponent<CompDisplayer>(comp_displayer);
	this->addComponent<CompCommunicator>(comp_communicator);


	return true;
}

void EnBullet::update()
{
	EntityBase::update();
}

void EnBullet::clear()
{

	//at end
	EntityBase::clear();
}

void EnBullet::addInfo(const AttackInfo & info)
{
	this->_attackInfo = info;

	auto compDisplayer = this->getComponent<CompDisplayer>(comp_displayer);
	compDisplayer->applySprite(_attackInfo.type_);

}

void EnBullet::flyToAim()
{
	if (_attackInfo.isNull())
	{
		
	}

	assert(0 && "info is not applied");
}

void EnBullet::destroySelf()
{
	MSGDISPATCHER->addMsg(next_frame, this->id(), selfMsgReceiver_id, MsgType::msg_destroy_self, nullptr);
}
