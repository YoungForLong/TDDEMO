#include "CompDisplayer.h"
#include "CompMoving.h"
#include "EntityBase.h"
#include <numeric>
#include "CommonUtils.h"

bool CompDisplayer::init()
{
	if (!root)
		return false;

	// 有几种类型需要手动添加图片名
	if(root->type() != environment)
		applySprite(root->type());

	return true;
}

void CompDisplayer::update()
{
	auto moving = root->getComponent<CompMoving>(ComponentType::comp_moving);
	
	if (moving)
	{
		_sprite->setPosition(transformToVisionPosition(moving->position()));
		
		//现在的方向是之前固定帧数的平均值
		_latestHeadings.push(moving->heading());
		if (_latestHeadings.size() >= smoothing_frames)
		{
			_latestHeadings.pop();
		}

		auto equalArr = _latestHeadings._Get_container();

		auto th = accumulate(equalArr.begin(), equalArr.end(), Vec2::ZERO);
		_sprite->setRotation(CU->transformHeadingToRotation(th));
	}
}

void CompDisplayer::clear()
{
	_sprite->release();
	_sprite->removeFromParent();
}

void CompDisplayer::applySprite(ObjectType type)
{
	auto name = CU->getConfigByKey(type, "spritename").asString() + ".png";
	_sprite = CREATE_SPRITE(name);
	_sprite->retain();
}

void CompDisplayer::applySprite(const string & filename)
{
	_sprite = CREATE_SPRITE(filename);
	_sprite->retain();
}

Vec2 CompDisplayer::transformToVisionPosition(const Vec2& pos)
{
	Vec2 halfScreen = Vec2(screen_width, screen_height) / 2.0f;

	return halfScreen + pos - OMGR->pos_of_camera;
}
