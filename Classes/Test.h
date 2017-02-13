#pragma once

#include "EntityBase.h"
#include "WaterEffect.h"

class EnShip;

class TestLayer :public Layer
{
public:
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(TestLayer);

	virtual void update(float fl) override;

	void addTouchReact();
private:
	EnShip* _hero;
};
