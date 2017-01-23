#pragma once

#include "EntityBase.h"
#include "WaterEffect.h"

class TestLayer :public Layer
{
public:
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(TestLayer);

	virtual void update(float fl) override;

	void addTouchReact();
private:
	EntityBase* _entity1;
	EntityBase* _entity2;
	Sprite* _testShip;
	vector<Sprite*> _bgSps;
	Vec2 _toTarget;

	GLProgramState* _we;
};
