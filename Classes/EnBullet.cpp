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
	
	this->_type = _attackInfo.type_;

	auto compDisplayer = this->getComponent<CompDisplayer>(comp_displayer);
	compDisplayer->applySprite(_attackInfo.type_);
	compDisplayer->setLayer(static_cast<Layer*>(
		Director::getInstance()->getRunningScene()->getChildByName("world")), world_above_sea_zorder);

	auto compMoving = this->getComponent<CompMoving>(comp_moving);
	compMoving->setPostion(_attackInfo.position_);
	compMoving->setHeading(_attackInfo.heading_);
	compMoving->setSpeed(/*CU->getConfigByKey(_attackInfo.type_, "speed").asFloat()*/10);

	auto compCommunicator = this->getComponent<CompCommunicator>(comp_communicator);
	
	compMoving->onArrive = [compCommunicator,this]() {
		//发送打击到的消息
		int* attackTypeFlag = new int(_attackInfo.typeFlag_);
		compCommunicator->sendMsg(0, id(), _attackInfo.target_, msg_on_attack, attackTypeFlag);
		
		//删除子弹本身
		this->destroySelf();
	};

}

void EnBullet::flyToAim()
{
	if (!_attackInfo.isNull())
	{
		auto compMoving = this->getComponent<CompMoving>(comp_moving);
		auto target = OMGR->getEntityById(_attackInfo.target_);

		compMoving->setTarget(target->getComponent<CompMoving>(comp_moving));
		
		return;
	}

	assert(0 && "info is not applied");
}

void EnBullet::destroySelf()
{
	MSGDISPATCHER->addMsg(next_frame, this->id(), selfMsgReceiver_id, MsgType::msg_destroy_self, nullptr);
}
