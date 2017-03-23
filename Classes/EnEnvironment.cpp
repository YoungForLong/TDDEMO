#include "EnEnvironment.h"
#include "ComponentDependencies.h"


bool EnEnvironment::init()
{
	if(!EntityBase::init())
		return false;

	auto cm = this->addComponent<CompMoving>(comp_moving);
	cm->setActive(false);

	auto cd = this->addComponent<CompDisplayer>(comp_displayer);
	cd->applySprite("island_1.png");

	return true;
}

void EnEnvironment::update()
{
	EntityBase::update();
}

void EnEnvironment::clear()
{

	EntityBase::clear();
}
