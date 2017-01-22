#pragma once

#include "EntityBase.h"

class TestLayer :public Layer
{
public:
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(TestLayer);

	virtual void update(float fl) override;

private:
	EntityBase* _entity1;
	EntityBase* _entity2;
};
