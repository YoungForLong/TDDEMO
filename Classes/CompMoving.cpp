#include "CompMoving.h"
#include "Cell_Space_Partition.h"
#include "Tranformation.h"

bool CompMoving::init()
{
	if (!root)
		return false;

	_position = Vec2::ZERO;
	_speed = 0.0f;
	_velocity = Vec2::ZERO;
	_heading = Vec2::ZERO;
	
	_cv = CollisionVolume();
	_cv.circle_.push_back(Circle(20, Vec2(0, 0), 0, 360));
	_cv.totalWidth_ = 20;
	_cv.totalHeight_ = 20;

	_target = nullptr;
	_aimPos = illegal_aim;
	_dBoxLength = 40;

	CSP->addEntity(this);

	return true;
}

void CompMoving::update()
{
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

	std::vector<CompMoving*> obstacles = CSP->getObstacles(this, _dBoxLength);

	if (!obstacles.empty())
	{
		auto obsAvoi_force = obstacleAvoidance(obstacles)*ObsAvoiWeight;

		totalForce += obsAvoi_force;
	}
		

	_velocity = totalForce.getNormalized()*_speed;

	_heading = _velocity.getNormalized();
	

	//calculate pos
	auto temp = _position;
	_position += _velocity*ADT;
	CSP->updateEntity(this, temp);
}

void CompMoving::clear()
{
}

const Vec2 CompMoving::seek(Vec2 aimPos)
{
	auto toTarget = aimPos - _position;
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
			float expandedRadius = obstacle->getBoundingRadius() + getBoundingRadius();

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

const CollisionVolume CompMoving::getCV()const
{
	CollisionVolume CV;
	int count = 0;
	while (count < _cv.circle_.size())
	{
		Circle c1 = _cv.circle_[count];
		CV.circle_.push_back(Circle(c1.radius_, c1.center_ + _position, 0, 360));
		count++;
	}
	count = 0;
	while (count < _cv.rect_.size())
	{
		Rect r1 = _cv.rect_[count];
		CV.rect_.push_back(Rect(r1.origin.x + _position.x, r1.origin.y + _position.y, r1.size.width, r1.size.height));
		count++;
	}

	return CV;
}

const float CompMoving::getBoundingRadius() const
{
	return 0.5f* max(_cv.totalHeight_, _cv.totalWidth_)*2.0f;
}
