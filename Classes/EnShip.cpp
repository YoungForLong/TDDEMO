#include "EnShip.h"
#include "ComponentDependencies.h"

bool EnShip::init()
{
	if (!EntityBase::init())
		return false;

	auto cm = this->addComponent<CompMoving>(comp_moving);
	cm->setSpeed(4);
	
	auto cc = this->addComponent<CompCommunicator>(comp_communicator);
	
	auto cb = this->addComponent<CompBattle>(comp_battle);
	
	this->addComponent<CompDisplayer>(comp_displayer);
	
	//test
	this->addComponent<CompControllerTest>(comp_controller_test);

	cc->handleMsg = [cb](const Telegram& msg)->bool {

		if (msg.msg_ == msg_on_attack)
		{
			cb->onAttacked();
			return true;
		}

		return false;
	};

	return true;
}

void EnShip::update()
{
	EntityBase::update();
}

void EnShip::clear()
{

	//at end
	EntityBase::clear();
}