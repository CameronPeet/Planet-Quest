//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// File Name		:	Entity.cpp
// Description	:	Entity implementation file.
// Author		:	 Cameron Peet
// Mail			:   Cameron.Peet@mediadesign.school.nz
//

#include "Entity.h"

/**
*
* Constructor.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return void
*
*/
CEntity::CEntity()
{
}

/**
*
* Destructor.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return void
*
*/
CEntity::~CEntity()
{
}

/**
*
* This function initialises the entity.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _location This is the location.
* @param _velocity This is the velocity.
* @return void
*
*/
void CEntity::Initialise(vec3 _location, vec3 _velocity)
{
	m_acceleration = vec3(0.0f, 0.0f, 0.0f);
	m_velocity = _velocity;
	m_location = _location;

	//Arbitrary values for maxspeed and force, try varying these!
	m_fMaxspeed = 1.0f;
	m_fMaxforce = 0.1f;

	m_model = new Model(m_shape, m_strFilename);
	m_model->Initialise();
	m_model->SetPosition(_location);
	m_bIsActive = true;
}

/**
*
* This function sets the scale of the entity.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _scale This is the scale.
* @return void
*
*/
void CEntity::SetScale(vec3 _scale)
{
	m_model->m_Scale = _scale;
}

/**
*
* This function processes the entity, using the standard “Euler integration” motion model.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _deltaTime This is the delta time.
* @return void
*
*/
void CEntity::Process(GLfloat _deltaTime)
{
	//m_velocity += m_acceleration * _deltaTime;
	//m_velocity = it(m_fMaxspeed, m_velocity);
	//m_location += m_velocity * _deltaTime;
	//m_acceleration *= 0;
	
	m_location += m_velocity * 2.0f * _deltaTime;
	m_model->SetPosition(m_location);
}

/**
*
* This function updates the entity, using the standard “Euler integration” motion model.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _deltaTime This is the delta time.
* @return void
*
*/
vec3 CEntity::Update(GLfloat _deltaTime)
{
	m_velocity += m_acceleration;
	if (length(m_velocity) > 0)
	{
		m_velocity = it(m_fMaxspeed, m_velocity);
		m_location += m_velocity * _deltaTime;
	}
	m_acceleration *= 0;

	m_model->SetPosition(m_location);

	return m_location;
}

/**
*
* This function sets the position the entity/.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _position This is the position.
* @return void
*
*/
void CEntity::SetPosition(vec3 _position)
{
	m_location = _position;
}

/**
*
* This function aplies force to the entity, using Newton's second law.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _force This is the force.
* @return void
*
*/
void CEntity::ApplyForce(vec3 _force)
{
	_force.y = 0;
	m_acceleration += _force;
}

/**
*
* This function limits a vector to a maximum value.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _fMax This is the maximum value.
* @param _vector This is the vector.
* @return Returns the resultant vector.
*
*/
vec3 CEntity::it(float _fMax, vec3 _vector)
{
	float fMagnitude = length(_vector);

	if (fMagnitude > _fMax)
	{
		if (length(_vector) > 0)
		{
			_vector = normalize(_vector);
		}
		_vector *= _fMax;
	}

	return _vector;
}

/**
*
* This function sets the velocity of the entity.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _velocity This is the velocity.
* @return void
*
*/
void CEntity::SetVelocity(vec3 _velocity)
{
	m_velocity = _velocity;
}

/**
*
* This function gets the location of the entity.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return Returns the location.
*
*/
vec3 CEntity::GetLocation()
{
	return m_location;
}

/**
*
* This function gets the velocity of the entity.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return Returns the velocity.
*
*/
vec3 CEntity::GetVelocity()
{
	return m_velocity;
}

/**
*
* This function applies the seek steering force.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _target This is the target.
* @return void
*
*/
void CEntity::Seek(vec3 _target)
{
	vec3 steer = SeekFunction(_target);

	ApplyForce(steer);
}

/**
*
* This function applies the flee steering force.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _target This is the target.
* @return void
*
*/
void CEntity::Flee(vec3 _target)
{
	vec3 steer = FleeFunction(_target);

	ApplyForce(steer);
}

/**
*
* This function applies the arrive steering force.
* (Task ID: Entity)
*
* @author   
* @param _target This is the target.
* @return void
*
*/
void CEntity::Arrive(vec3 _target)
{
	vec3 steer = ArriveFunction(_target);

	ApplyForce(steer);
}

/**
*
* This function applies the wander steering force.
* (Task ID: Entity)
*
* @author  
* @param void
* @return void
*
*/
void CEntity::Wander()
{
	vec3 steer = WanderFunction();

	ApplyForce(steer);
}

/**
*
* This function applies the containment steering force.
* (Task ID: Entity)
*
* @author  
* @param void
* @return Returns true if the entity is inside the area, false if not.
*
*/
bool CEntity::Containment()
{
	vec3 desired;
	//vec3 desired = vec3(0.0f, 0.0f, 0.0f) - m_location;
	if (m_location.x > 7.0f || m_location.x < -7.0f)
	{
		// Make a desired vector that retains the y direction of the vehicle 
		// but points the x direction directly away from the window’s left edge.
		desired = vec3(m_fMaxspeed, 0.0f, m_velocity.z) - m_location;
		//vec3 desired = vec3(0, 0, 0) - m_location;
	}
	else if (m_location.z > 7.0f || m_location.z < -7.0f)
	{
		desired = vec3(m_velocity.x, 0.0f, m_fMaxspeed) - m_location;
	}
	else
	{
		return true;
	}

	vec3 steer = desired - m_velocity;
	steer = it(m_fMaxforce, desired);

	ApplyForce(steer);

	return false;
}

/**
*
* This function applies the pursuit steering force.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return void
*
*/
void CEntity::Pursuit(CEntity _target)
{
	vec3 steer = PursuitFunction(_target);

	ApplyForce(steer);
}

/**
*
* This function applies the evade steering force.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return void
*
*/
void CEntity::Evade(CEntity _target)
{
	vec3 steer = EvadeFunction(_target);

	ApplyForce(steer);
}

/**
*
* This function computes the seek steering force.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3 CEntity::SeekFunction(vec3 _target)
{
	vec3 desired = _target - m_location;
	if (length(desired) > 0)
	{
		desired = normalize(desired);
	}
	//Calculating the desired velocity to target at max speed
	desired *= m_fMaxspeed;

	//Reynolds’s formula for steering force
	vec3 steer = desired - m_velocity;
	// it the magnitude of the steering force.
	steer = it(m_fMaxforce, steer);

	//Instead of applying the force we return the PVector.
	//ApplyForce(steer);
	return steer;
}

/**
*
* This function computes the flee steering force.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3 CEntity::FleeFunction(vec3 _target)
{
	//vec3 steer = SeekFunction(_target);
	//steer *= -1;

	vec3 desired = m_location - _target;
	if (length(desired) > 0)
	{
		desired = normalize(desired);
	}
	//Calculating the desired velocity to target at max speed
	desired *= m_fMaxspeed;

	//Reynolds’s formula for steering force
	vec3 steer = desired - m_velocity;
	// it the magnitude of the steering force.
	steer = it(m_fMaxforce, steer);

	return steer;
}

/**
*
* This function computes the arrive steering force.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3  CEntity::ArriveFunction(vec3 _target)
{
	vec3 desired = _target - m_location;

	// The distance is the magnitude of the vector pointing from location to target.
	float fMagnitude = length(desired);

	if (length(desired) > 0)
	{
		desired = normalize(desired);
	}

	float fNearRadius = 2.0f;

	// If we are closer than 2 pixels...
	if (fMagnitude < fNearRadius) 
	{
		//...set the magnitude according to how close we are.
		//float fNewSpeed = map(fMagnitude, 0, 100, 0, m_fMaxspeed);
		float fSpeed = m_fMaxspeed * fMagnitude / fNearRadius;

		desired *= fSpeed;
	}
	else {
		// Otherwise, proceed at maximum speed.
		desired *= m_fMaxspeed;
	}
	// The usual steering = desired - velocity
	vec3 steer = desired - m_velocity;
	steer = it(m_fMaxforce, steer);

	return steer;
}

/**
*
* This function computes the wander steering force.
* (Task ID: Entity)
*
* @author 
* @param _target void
* @return Returns the steering force.
*
*/
vec3 CEntity::WanderFunction()
{
	float fRadius = 1.0f;
	float fDistance = 2.0f;

	//initialise velocity

	vec3 desired = m_velocity; // = _target - m_location;
	if (length(desired) > 0)
	{
		desired = normalize(desired);
	}
	desired *= fDistance;

	int iTheta = (rand() % 360);

	vec3 target = vec3(fRadius * cos(iTheta), 0.0f, fRadius * sin(iTheta));

	desired = desired + target;
	if (length(desired) > 0)
	{
		desired = normalize(desired);
	}
	desired *= m_fMaxspeed;

	vec3 steer = desired - m_velocity;

	steer = it(m_fMaxforce, steer);

	return steer;

}

/**
*
* This function computes the pursuit steering force.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3 CEntity::PursuitFunction(CEntity _target)
{
	vec3 _targetPosition = _target.m_location;
	vec3 _targetVelocity = _target.m_velocity;

	vec3 ToEvader = _targetPosition - m_location;

	float RelativeHeading = dot(m_velocity, _targetVelocity);

	vec3 steer;

	if ((dot(ToEvader, m_velocity) > 0) && (RelativeHeading < 0.95))
	{
		steer = SeekFunction(_targetPosition);
	}
	else
	{
		float LookAheadTime = length(_targetPosition - m_location) / (m_fMaxspeed + length(_targetVelocity));

		steer = SeekFunction(_targetPosition + _targetVelocity * LookAheadTime);
	}

	return steer;
}

/**
*
* This function computes the evade steering force.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3 CEntity::EvadeFunction(CEntity _target)
{
	vec3 _targetPosition = _target.m_location;
	vec3 _targetVelocity = _target.m_velocity;

	vec3 ToEvader = _targetPosition - m_location;

	float RelativeHeading = dot(m_velocity, _targetVelocity);

	vec3 steer;

	if ((dot(ToEvader, m_velocity) > 0) && (RelativeHeading < 0.95))
	{
		steer = FleeFunction(_targetPosition);
	}
	else
	{
		float LookAheadTime = length(_targetPosition - m_location) / (m_fMaxspeed + length(_targetVelocity));

		steer = FleeFunction(_targetPosition + _targetVelocity * LookAheadTime);
	}

	return steer;
}

/**
*
* This function computes steering force to evade the leader.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target
* @return Returns the steering force.
*
*/
vec3 CEntity::EvadeLeader(CEntity _target)
{
	vec3 _targetPosition = _target.m_location;
	vec3 _targetVelocity = _target.m_velocity;

	float LookAheadTime = length(_targetPosition - m_location) / (m_fMaxspeed + length(_targetVelocity));

	vec3 steer = FleeFunction(_targetPosition + _targetVelocity * LookAheadTime);

	return steer;
}

/**
*
* This function computes the separation steering force.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return Returns the steering force.
*
*/
vec3 CEntity::Separation(std::vector<CEntity*> _vecEntities)
{
	// This variable specifies how close is too close.
	//Note how the desired separation is based on the Vehicle’s size.
	float desiredseparation = GetWidth() * 1.5f;

	vec3 sum;

	int iCount = 0;

	//We have to keep track of how many Vehicles are too close.
	for each (CEntity* _entity in _vecEntities)
	{
		if (!_entity->m_bIsHit)
		{
			vec3 diff = m_location - _entity->GetLocation();
			// What is the distance between me and another Vehicle ?
			float fDistance = length(diff);

			if ((fDistance > 0) && (fDistance < desiredseparation))
			{
				//Any code here will be executed if the entity is within 5 pixels.
				if (length(diff) > 0)
				{
					diff = normalize(diff);
				}
				//What is the magnitude of the PVector pointing away from the other vehicle ? 
				//The closer it is, the more we should flee.The farther, the less.
				//So we divide by the distance to weight it appropriately.
				diff /= fDistance;
				//Add all the vectors together and increment the count.
				sum += diff;
				iCount++;

			}
		}	
	}
	//We have to make sure we found at least one close vehicle.
	//We don’t want to bother doing anything if nothing is too close(not to mention we can’t divide by zero!)
	if (iCount > 0)
	{
		sum /= iCount;
		if (length(sum) > 0)
		{
			sum = normalize(sum);
		}
		//Scale average to maxspeed(this becomes desired).
		sum *= m_fMaxspeed;
		//Reynolds’s steering formula
		vec3 steer = sum - m_velocity;
		steer = it(m_fMaxforce, steer);
		//Apply the force to the Vehicle’s acceleration.
		//ApplyForce(steer);

		return steer;
	}
	else
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}
}

/**
*
* This function computes the cohesion steering force.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return Returns the steering force.
*
*/
vec3 CEntity::Cohesion(std::vector<CEntity*> _vecEntities)
{
	float fNeighbourDistance = 5;
	vec3 sum;
	int iCount = 0;

	for each (CEntity* _entity in _vecEntities)
	{
		vec3 diff = m_location - _entity->GetLocation();
		float fDistance = length(diff);

		if ((fDistance > 0) && (fDistance < fNeighbourDistance))
		{
			//Adding up all the others’ locations
			sum += _entity->GetLocation();

			iCount++;
		}
	}
	if (iCount > 0)
	{
		sum /= iCount;

		//Here we make use of the seek() function we wrote in Example 6.8.
		//The target we seek is the average location of our neighbors.

		return SeekFunction(sum);
	}
	else
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}
}

/**
*
* This function computes the alignment steering force.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return Returns the steering force.
*
*/
vec3 CEntity::Alignment(std::vector<CEntity*> _vecEntities)
{
	//This is an arbitrary value and could vary from boid to boid.
	float fNeighbourDistance = 5;
	vec3 sum;
	int iCount = 0;

	for each (CEntity* _entity in _vecEntities)
	{
		vec3 diff = m_location - _entity->GetLocation();
		float fDistance = length(diff);

		if ((fDistance > 0) && (fDistance < fNeighbourDistance))
		{
			sum += _entity->GetVelocity();
			//For an average, we need to keep track of how many boids are within the distance.
			iCount++;
		}
	}
	if (iCount > 0)
	{
		sum /= iCount;
		if (length(sum) > 0)
		{
			sum = normalize(sum);
		}
		sum *= m_fMaxspeed;
		vec3 steer = sum - m_velocity;
		steer = it(m_fMaxforce, steer);
		return steer;
	}
	else
	{
		//If we don’t find any close boids, the steering force is zero.
		return vec3(0.0f, 0.0f, 0.0f);
	}
}

/**
*
* This function applies flocking.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::Flocking(std::vector<CEntity*> _vecEntities)
{
	//The three flocking rules
	vec3 separate = Separation(_vecEntities);
	vec3 align = Alignment(_vecEntities);
	vec3 cohere = Cohesion(_vecEntities);

	//Arbitrary weights for these forces(Try different ones!)
	separate *= 2.0f;
	align *= 1.0f;
	cohere *= 1.5f;

	//Applying all the forces
	ApplyForce(separate);
	ApplyForce(align);
	ApplyForce(cohere);
}

/**
*
* This function applies leader following.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::FollowLeader(CEntity _Leader, std::vector<CEntity*> _vecEntities)
{
	vec3 leaderPosition = _Leader.m_location;
	vec3 leaderVelocity = _Leader.m_velocity;

	float fDistanceBehindLeader = _Leader.GetWidth();

	// Calculate the ahead point
	vec3 targetVelocity = leaderVelocity;

	//normalizing fails with 0 velocity
	if (length(targetVelocity) > 0)
	{
		targetVelocity = normalize(targetVelocity);
	}
	//therefore make sure the enemies stop somewhere at a distance to the leader
	else
	{
		//targetVelocity = vec3(0.0f, 0.0f, 1.0f);
	}
	targetVelocity *= fDistanceBehindLeader;
	vec3 ahead = leaderPosition + targetVelocity;

	// Calculate the behind point
	targetVelocity *= -1;
	vec3 behind = leaderPosition + targetVelocity;

	vec3 evade = vec3(0.0f, 0.0f, 0.0f);
	// If the character is on the leader's sight, add a force
	// to evade the route immediately.
	if (isOnLeaderSight(leaderPosition, ahead))
	{
		evade = EvadeLeader(_Leader);
	}

	vec3 arrive = ArriveFunction(behind);
	vec3 separate = Separation(_vecEntities);

	evade *= 5.0f;
	arrive *= 1.0f;
	separate *= 1.5f;

	ApplyForce(evade);
	ApplyForce(arrive);
	ApplyForce(separate);
}

/**
*
* This function checks if the entity is on the leader's sight.
* (Task ID: Entity)
*
* @author  
* @param _LeaderPosition This is the leader's position.
* @param _Ahead This is the ahead position.
* @return Returns true if it is on the leader's sight, false if not.
*
*/
bool CEntity::isOnLeaderSight(vec3 _LeaderPosition, vec3 _Ahead)
{
	float fLeaderSightRadius = 2.5f;

	float _distanceToAhead = length(_Ahead - m_location);
	float _distanceToLeader = length(_LeaderPosition - m_location);

	return (_distanceToAhead <= fLeaderSightRadius) || (_distanceToLeader <= fLeaderSightRadius);
}

/**
*
* This function translates the entity.
* (Task ID: Entity)
*
* @author  
* @param delta This is the velocity.
* @return void
*
*/
void CEntity::Translate(vec3 delta)
{
	m_location += delta;
	m_velocity = delta;

	//m_model->SetPosition(m_location);
}

/**
*
* This function applies seek and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::SeekSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 seek = SeekFunction(_target);

	separate *= 2.0f;
	seek *= 1.0f;

	ApplyForce(separate);
	ApplyForce(seek);
}

/**
*
* This function applies flee and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::FleeSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 flee = FleeFunction(_target);

	separate *= 2.0f;
	flee *= 1.0f;

	ApplyForce(separate);
	ApplyForce(flee);
}

/**
*
* This function applies arrive and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ArriveSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 arrive = ArriveFunction(_target);

	separate *= 2.0f;
	arrive *= 1.0f;

	ApplyForce(separate);
	ApplyForce(arrive);
}

/**
*
* This function applies pursuit and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::PursuitSeparate(CEntity _target, std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 pursuit = PursuitFunction(_target);

	separate *= 2.0f;
	pursuit *= 1.0f;

	ApplyForce(separate);
	ApplyForce(pursuit);
}

/**
*
* This function applies evade and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::EvadeSeparate(CEntity _target, std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 pursuit = EvadeFunction(_target);

	separate *= 2.0f;
	pursuit *= 1.0f;

	ApplyForce(separate);
	ApplyForce(pursuit);
}

/**
*
* This function applies wander and separate.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::WanderSeparate(std::vector<CEntity*> _vecEntities)
{
	vec3 separate = Separation(_vecEntities);
	vec3 wander = WanderFunction();

	separate *= 2.0f;
	wander *= 1.0f;

	ApplyForce(separate);
	ApplyForce(wander);
}

/**
*
* This function applies wander and obstacle avoidance.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::WanderAvoidObstacle(std::vector<CEntity*> _vecEntities)
{
	vec3 avoidObstacle = ObstacleAvoidance(_vecEntities);
	vec3 wander = WanderFunction();

	avoidObstacle *= 1.0f;
	wander *= 5.0f;

	ApplyForce(avoidObstacle);
	ApplyForce(wander);
}

/**
*
* This function contains the seek and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainSeekSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		SeekSeparate(_target, _vecEntities);
	}
}

/**
*
* This function contains the arrive and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainArriveSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		ArriveSeparate(_target, _vecEntities);
	}
}

/**
*
* This function contains the pursuit and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainPursuitSeparate(CEntity _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		PursuitSeparate(_target, _vecEntities);
	}
}

/**
*
* This function contains the flee and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainFleeSeparate(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		FleeSeparate(_target, _vecEntities);
	}
}

/**
*
* This function contains the evade and separate.
* (Task ID: Entity)
*
* @author  
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainEvadeSeparate(CEntity _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		EvadeSeparate(_target, _vecEntities);
	}
}

/**
*
* This function contains the wandering.
* (Task ID: Entity)
*
* @author  
* @param void
* @return void
*
*/
void CEntity::ContainWander()
{
	if (Containment())
	{
		Wander();
	}
}

/**
*
* This function contains the flocking.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainFlocking(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		Flocking(_vecEntities);
	}
}

/**
*
* This function contains the separation.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainSeparate(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		vec3 separate = Separation(_vecEntities);
		ApplyForce(separate);
	}
}

/**
*
* This function contains the alignment.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainAlign(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		vec3 align = Alignment(_vecEntities);
		ApplyForce(align);
	}
}

/**
*
* This function contains the alignment and separation.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainAlignSeparate(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		vec3 separate = Separation(_vecEntities);
		vec3 align = Alignment(_vecEntities);

		ApplyForce(separate);
		ApplyForce(align);
	}
}

/**
*
* This function contains the cohesion and separation.
* (Task ID: Entity)
*
* @author 
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainCohesionSeparate(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		vec3 cohere = Cohesion(_vecEntities);
		vec3 separate = Separation(_vecEntities);

		ApplyForce(cohere);
		ApplyForce(separate);
	}
}

/**
*
* This function contains the cohesion.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainCohesion(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		vec3 cohesion = Cohesion(_vecEntities);
		ApplyForce(cohesion);
	}
}

/**
*
* This function contains the wander and separate.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainWanderSeparate(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		WanderSeparate(_vecEntities);
	}
}

/**
*
* This function contains the wander and obstacle avoidance.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainWanderAvoidObstacle(std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		WanderAvoidObstacle(_vecEntities);
	}
}

/**
*
* This function contains the leader following.
* (Task ID: Entity)
*
* @author  
* @param _Leader This is the leader.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainFollowLeader(CEntity _Leader, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		FollowLeader(_Leader, _vecEntities);
	}
}

/**
*
* This function contains the leader following.
* (Task ID: Entity)
*
* @author 
* @param _target This is the target.
* @param _vecEntities This is the group of entities.
* @return void
*
*/
void CEntity::ContainQueue(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	if (Containment())
	{
		QueueSeek(_target, _vecEntities);
	}
}

/**
*
* This function sets the model's position.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return void
*
*/
void CEntity::SetModelPosition()
{
	m_model->SetPosition(m_location);
}

/**
*
* This function draws the entity.
* (Task ID: Entity)
*
* @author Cameron Peet
* @param program This is the program.
* @param camera This is the camera.
* @return void
*
*/
void CEntity::Draw(GLuint program, Camera& camera)
{
	//m_model->Draw();
	if (m_bIsActive && !m_bIsHit)
	{
		m_model->Render(program, camera);
	}
}

/**
*
* This function gets the width of the model.
* (Task ID: Entity)
*
* @author Cameron Peet
* @param void
* @return Returns the width of the model
*
*/
float CEntity::GetWidth() const
{
	return (m_model->getScale().x);
}

/**
*
* This function gets the height of the model.
* (Task ID: Entity)
*
* @author Cameron Peet
* @param void
* @return Returns the height of the model
*
*/
float CEntity::GetHeight() const
{
	return (m_model->getScale().y);
}

/**
*
* This function gets the depth of the model.
* (Task ID: Entity)
*
* @author Cameron Peet
* @param void
* @return Returns the depth of the model
*
*/
float CEntity::GetDepth() const
{
	return(m_model->getScale().z);
}

/**
*
* This function gets the model.
* (Task ID: Entity)
*
* @author Cameron Peet
* @param void
* @return Returns the model
*
*/
Model* CEntity::GetModel()
{
	return m_model;
}

/**
*
* This function checks if a line intersects a circle.
* (Task ID: Entity)
*
* @author  
* @param _ahead line 1
* @param _ahead2 line 2
* @param _Obstacle the circle
* @return Returns true if intersects, fasle if not
*
*/
bool CEntity::lineIntersectsCircle(vec3 _ahead, vec3 _ahead2, CEntity* _Obstacle)
{
	// the property "center" of the obstacle is a Vector3D.
	float distanceAhead = length(_Obstacle->m_location - _ahead);
	float distanceAhead2 = length(_Obstacle->m_location - _ahead2);
	float obstacleRadius = 2.0f;
	return (distanceAhead <= obstacleRadius || distanceAhead2 <= obstacleRadius);
}

/**
*
* This function implements obstacle avoidance.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities Group of obstacles.
* @return Returns the steering force.
*
*/
vec3 CEntity::ObstacleAvoidance(std::vector<CEntity*> _vecEntities)
{
	float dynamic_length = length(m_velocity) / m_fMaxspeed;
	vec3 normVelocity = m_velocity;
	if (length(m_velocity) > 0)
	{
		normVelocity = normalize(m_velocity);
	}
	vec3 ahead = m_location + normVelocity * dynamic_length;
	float MAX_SEE_AHEAD = 2.0f;
	//ahead = m_location + normVelocity * MAX_SEE_AHEAD;
	vec3 ahead2 = m_location + (normVelocity * MAX_SEE_AHEAD * 0.5f);
	ahead2 = m_location + (normVelocity * dynamic_length * 0.5f);

	CEntity* mostThreatening = findMostThreateningObstacle(_vecEntities, ahead, ahead2);
	vec3 avoidance = vec3(0.0f, 0.0f, 0.0f);

	if (mostThreatening != nullptr)
	{
		avoidance.x = ahead.x - mostThreatening->m_location.x;
		avoidance.z = ahead.z - mostThreatening->m_location.z;

		if (length(avoidance) > 0)
		{
			avoidance = normalize(avoidance);
		}
		//avoidance *= m_fMaxforce;
		avoidance *= 2.0f;
	}
	else
	{
		avoidance *= 0.0f;	// nullify the avoidance force
	}

	return avoidance;
}

/**
*
* This function finds the most threatening obstacle.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities Group of obstacles.
* @param _ahead line 1
* @param _ahead2 line 2
* @return Returns the most threatening obstacle.
*
*/
CEntity* CEntity::findMostThreateningObstacle(std::vector<CEntity*> _vecEntities, vec3 _ahead, vec3 _ahead2)
{
	CEntity* mostThreatening = nullptr;

	for each (CEntity* _obstacle in _vecEntities)
	{
		if (m_location != _obstacle->m_location)
		{
			bool collision = lineIntersectsCircle(_ahead, _ahead2, _obstacle);

			// "position" is the character's current position
			float distanceToObstacle = length(m_location - _obstacle->m_location);
			//float distanceToMostThreathening = length(m_location - mostThreatening->m_location);

			float distanceToMostThreathening = 0.0f;
			if (mostThreatening != nullptr)
			{
				distanceToMostThreathening = length(m_location - mostThreatening->m_location);
			}

			if (collision && (mostThreatening == nullptr || distanceToObstacle < distanceToMostThreathening))
			{
				mostThreatening = _obstacle;
			}
		}
	}

	return mostThreatening;
}

/**
*
* This function gets the nearest entity in front of you.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities Group of obstacles.
* @return Returns the nearest entity in front of you.
*
*/
CEntity* CEntity::getNeighbourAhead(std::vector<CEntity*> _vecEntities)
{
	CEntity* _neightbourAhead = nullptr;
	vec3 normVelocity = m_velocity;
	if (length(m_velocity) > 0)
	{
		normVelocity = normalize(m_velocity);
	}
	float MAX_QUEUE_AHEAD = 1.0f;
	normVelocity *= MAX_QUEUE_AHEAD;

	vec3 ahead = m_location + normVelocity;

	for (unsigned int i = 0; i < _vecEntities.size(); i++)
	{
		CEntity* neighbour = _vecEntities[i];
		float distance = length(ahead - neighbour->m_location);
		float MAX_QUEUE_RADIUS = 1.0f;
		if (neighbour != this && distance <= MAX_QUEUE_RADIUS)
		{
			_neightbourAhead = neighbour;
			break;
		}
	}

	return _neightbourAhead;
}

/**
*
* This function implements queueing.
* (Task ID: Entity)
*
* @author  
* @param _vecEntities Group of obstacles.
* @return Returns the steering force.
*
*/
vec3 CEntity::QueueFunction(std::vector<CEntity*> _vecEntities)
{
	CEntity* neighbor = getNeighbourAhead(_vecEntities);

	if (neighbor != nullptr)
	{
		// take action because neighbor is ahead
		m_velocity *= 0.3f;
	}
	//steer = it(m_fMaxforce, steer);

	return vec3(0.0f, 0.0f, 0.0f);
}

/**
*
* This function implements queue and seek.
* (Task ID: Entity)
*
* @author  
* @param _target The player.
* @param _vecEntities Group of obstacles.
* @return void
*
*/
void CEntity::QueueSeek(vec3 _target, std::vector<CEntity*> _vecEntities)
{
	vec3 seek = SeekFunction(_target);
	vec3 queue = QueueFunction(_vecEntities);
	//vec3 separate = Separation(_vecEntities);

	seek *= 1.0f;
	queue *= 1.0f;
	//separate *= 1.0f;

	ApplyForce(seek);
	ApplyForce(queue);
	//ApplyForce(separate);
}

/**
*
* This function sets max speed.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param _maxSpeed This is the speed.
* @return void
*
*/
void CEntity::setMaxSpeed(float _maxSpeed)
{
	m_fMaxspeed = _maxSpeed;
}

/**
*
* This function gets max speed.
* (Task ID: Entity)
*
* @author  Cameron Peet
* @param void
* @return Returns the max speed
*
*/
float CEntity::getMaxSpeed()
{
	return m_fMaxspeed;
}

