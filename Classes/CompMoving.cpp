#include "CompMoving.h"
#include "Cell_Space_Partition.h"
#include "Transformation.h"
#include "CommonUtils.h"
#include "EntityBase.h"
#include "Circle.h"
#include "SlantRect.h"

const float CompMoving::getBoundingRadius()
{
	if (_cv->type_ == circle)
	{
		Circle* cir = static_cast<Circle*>(_cv);

		return cir->radius_;
	}

	assert(0 && "not a circle");
	return 0.0f;
}

bool CompMoving::init()
{
	if (!root)
		return false;

	_position = Vec2::ZERO;
	_speed = 0.0f;
	_velocity = Vec2(1, 0);
	_heading = Vec2(1, 0);
	_target = nullptr;
	_aimPos = illegal_aim;
	onArrive = nullptr;
	_rSpeed = 0;
	_active = true;

	loadMovingConfig();

	CSP->addEntity(this);

	return true;
}

void CompMoving::update()
{
	if (!_active)
		return;

	//calculate velocity
	Vec2 totalForce = Vec2::ZERO;
	if (_target != nullptr)
	{
		totalForce += pursuit(_target)*PursuitWeight;
	}
	else if (((_aimPos - illegal_aim).getLengthSq() > 0.01f) && (_aimPos - _position).getLengthSq() > 0.001)
	{
		totalForce += seek(_aimPos)*SeekWeight;
	}
	else
	{
		return;
	}

	//calculate resistance
	if (!this->_canCross)
	{
		std::vector<CompMoving*> obstacles = CSP->getObstacles(this, _dBoxLength);

		if (!obstacles.empty())
		{
			auto obsAvoi_force = obstacleAvoidance(obstacles)*ObsAvoiWeight;
			/*CCLOG("seek force: %f,%f", totalForce.x, totalForce.y);
			CCLOG("obs force: %f,%f", obsAvoi_force.x, obsAvoi_force.y);*/
			//CU->testNumArr.push_back(obsAvoi_force.getLength());
			totalForce += obsAvoi_force;
		}
	}
		
	if (totalForce != Vec2::ZERO)
	{
		_velocity += totalForce;
		_velocity = _velocity.getNormalized()*_speed;

		_heading = _velocity.getNormalized();

		//calculate pos
		auto temp = _position;

		if (syncHeading())
		{
			_position += _velocity;
			CSP->updateEntity(this, temp);
		}
	}
}

void CompMoving::clear()
{
	CSP->removeEntity(this);
	
	delete _cv;
	_cv = NULL;
}

void CompMoving::loadMovingConfig()
{
	_speed = CU->getConfigByKey(root->type(), "speed").asFloat();

	_cv = new Circle(80, _position);

	_rSpeed = CU->getConfigByKey(root->type(), "rspeed").asFloat();

	_dBoxLength = 160;

	_canCross = CU->getConfigByKey(root->type(), "cancross").asBool();
}

const Vec2 CompMoving::seek(Vec2 aimPos)
{
	auto toTarget = aimPos - _position;
	if (toTarget.getLengthSq() < _speed*_speed )
	{
		if (onArrive)
		{
			onArrive();
		}

		_target = nullptr;
		_aimPos = illegal_aim;

		return toTarget;
	}
	return toTarget.getNormalized()*_speed;
}

const Vec2 CompMoving::pursuit(CompMoving * target)
{
	Vec2 toEvader = target->position() - _position;

	//dk how to descripe this angle,
	double relativeHeading = _heading.dot(target->heading());

	if (toEvader.dot(target->heading()) > 0/*are they face towards each-other*/
		&& (relativeHeading < -0.95))
	{
		return seek(target->position());
	}
	//ahead time
	double lookAheadTime = toEvader.getLength() / (_speed + target->speed());

	return seek(target->position() + target->velocity()*lookAheadTime);
}

const Vec2 CompMoving::flee(Vec2 aimPos)
{
	auto fromTarget = _position - aimPos;
	return fromTarget.getNormalized()*_speed;
}

const Vec2 CompMoving::evade(CompMoving * target)
{
	Vec2 toTarget = target->position() - _position;

	double lookAheadTime = toTarget.getLength() / (_speed + target->speed());

	return flee(target->position() + target->velocity()*lookAheadTime);
}

//const Vec2 CompMoving::obstacleAvoidance(vector<CompMoving*>& obstacles)
//{
//	//对所有碰撞体做斥力计算，然后求合力
//
//	Vec2 sumRepulsion = Vec2::ZERO;
//
//	for_each(obstacles.begin(), obstacles.end(),[this,&sumRepulsion](CompMoving* obs) {
//		Vec2 tempRepulsion = Vec2::ZERO;
//		if (this->getCV()->intersects(obs->getCV(), tempRepulsion))
//		{
//			sumRepulsion += tempRepulsion;
//		}
//	});
//
//	return sumRepulsion;
//}

const Vec2 CompMoving::obstacleAvoidance(vector<CompMoving*>& obstacles)
{
	//nearest intersection dis alone axis x
	double NIOL_x = max_float;

	//nearest intersection position on local
	Vec2 NIOL_po = Vec2::ZERO;

	//nearest obstacle
	CompMoving* NObstacle = NULL;

	//entities within view range
	std::vector<CompMoving*>& neighborObstacles = obstacles;

	//find the point of the force
	std::for_each(neighborObstacles.begin(), neighborObstacles.end(), [this, &NIOL_x, &NIOL_po, &NObstacle](CompMoving* obstacle)
	{
		Vec2 poOnLocal = PointToLocalSpace(obstacle->position(), _heading, _heading.getPerp(), _position);

		//tips: better to use "do while(0)" struct
		if (poOnLocal.x >= 0)
		{
			float expandedRadius = obstacle->getBoundingRadius() + 2*getBoundingRadius();

			if (fabs(poOnLocal.y) < expandedRadius)
			{
				float cY = fabs(poOnLocal.y) - getBoundingRadius();
				float dist = sqrt(expandedRadius*expandedRadius - (cY)*(cY));
				//find out the intersections
				double intersectionX = poOnLocal.x - dist;

				//just determined by the positive axis X
				if (intersectionX <= 0)
				{
					intersectionX = poOnLocal.x + dist;
				}

				if (intersectionX < NIOL_x)
				{
					NIOL_x = intersectionX;

					NIOL_po = poOnLocal;

					NObstacle = obstacle;
				}
			}
		}
	}
	);

	//caculate the force
	Vec2 steeringForce = Vec2::ZERO;

	//is obstacle exist
	if (NObstacle)
	{
		//no matter on the x or y, the closer, the stronger the for shouble be

		//the effect on x
		double multiplier = 1.0 + (_dBoxLength - NIOL_po.x) / _dBoxLength;
		//the effect on y
		steeringForce.y = (NObstacle->getBoundingRadius() - NIOL_po.y)*multiplier;

		//apply a braking force
		steeringForce.x = (NObstacle->getBoundingRadius() - NIOL_po.x)*BrakingWeight;
	}

	//convert the force from local to world space
	return VectorToWorldSpace(steeringForce, _heading, _heading.getPerp());
}

bool CompMoving::syncHeading()
{
	/*auto diffAngle = _velocity.getAngle(_heading);

	if (fabs(diffAngle) < _rSpeed)
	{
		_heading = _velocity.getNormalized();
		return true;
	}
	else
	{
		auto testAngle = -diffAngle / fabs(diffAngle)*_rSpeed * 180 / PI;

		_heading.rotate(Vec2::ZERO, -diffAngle / fabs(diffAngle)*_rSpeed);
	}

	return false;*/
	
	_heading = _velocity.getNormalized();
	return true;
}

void CompMoving::moveTo(Vec2 aimPos)
{
	_aimPos = aimPos;
}

void CompMoving::stop()
{
	_velocity = Vec2::ZERO;
}

void CompMoving::moveTowards(Vec2 h)
{
	moveTo(_position + h*_speed);
}

void CompMoving::setPostion(const Vec2 & pos)
{
	auto temp = _position;
	_position = pos;
	CSP->updateEntity(this, temp);
}

CollisionVolume* CompMoving::getCV()
{
	return _cv->realCV(_position, _heading);
}
