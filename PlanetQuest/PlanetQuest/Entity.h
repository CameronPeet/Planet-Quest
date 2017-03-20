//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// File Name		:	Entity.h
// Description	:	Entity declaration file.
// Author		:	 Cameron Peet
// Mail			:   Cameron.Peet@mediadesign.school.nz
//

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "glew.h"
#include "glm/glm.hpp"
#include "Model.h"

using namespace glm;


class CEntity
{
public:
	CEntity();
	virtual ~CEntity();

	virtual void Initialise(vec3 _location, vec3 _velocity);
	virtual void Draw(GLuint program, Camera& camera);
	virtual void Process(GLfloat _deltaTime);
	void SetPosition(glm::vec3 _position);
	vec3 Update(GLfloat _deltaTime);
	void ApplyForce(vec3 _force);

	// functions that apply forces
	void Seek(vec3 _target);
	void Flee(vec3 _target);
	void Arrive(vec3 _target);
	void Wander();
	bool Containment();
	void Pursuit(CEntity _target);
	void Evade(CEntity _target);
	vec3 ObstacleAvoidance(std::vector<CEntity*> _vecEntities);

	// functions that compute and return the steering vector - no forces applied
	// this is used in combining steering forces
	vec3 SeekFunction(vec3 _target);
	vec3 FleeFunction(vec3 _target);
	vec3 ArriveFunction(vec3 _target);
	vec3 WanderFunction();
	vec3 PursuitFunction(CEntity _target);
	vec3 EvadeFunction(CEntity _target);
	vec3 EvadeLeader(CEntity _target);
	vec3 Separation(std::vector<CEntity*> _vecEntities);
	vec3 Cohesion(std::vector<CEntity*> _vecEntities);
	vec3 Alignment(std::vector<CEntity*> _vecEntities);
	vec3 QueueFunction(std::vector<CEntity*> _vecEntities);

	// Functions that combine steering forces
	void Flocking(std::vector<CEntity*> _vecEntities);
	void FollowLeader(CEntity _Leader, std::vector<CEntity*> _vecEntities);
	void SeekSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void FleeSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void ArriveSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void WanderSeparate(std::vector<CEntity*> _vecEntities);
	void WanderAvoidObstacle(std::vector<CEntity*> _vecEntities);
	void PursuitSeparate(CEntity _target, std::vector<CEntity*> _vecEntities);
	void EvadeSeparate(CEntity _target, std::vector<CEntity*> _vecEntities);
	void QueueSeek(vec3 _target, std::vector<CEntity*> _vecEntities);

	// Functions that combine steering forces - all with containment
	void ContainSeekSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void ContainArriveSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void ContainPursuitSeparate(CEntity _target, std::vector<CEntity*> _vecEntities);
	void ContainFleeSeparate(vec3 _target, std::vector<CEntity*> _vecEntities);
	void ContainEvadeSeparate(CEntity _target, std::vector<CEntity*> _vecEntities);
	void ContainWander();
	void ContainFlocking(std::vector<CEntity*> _vecEntities);
	void ContainSeparate(std::vector<CEntity*> _vecEntities);
	void ContainAlign(std::vector<CEntity*> _vecEntities);
	void ContainAlignSeparate(std::vector<CEntity*> _vecEntities);
	void ContainCohesionSeparate(std::vector<CEntity*> _vecEntities);
	void ContainCohesion(std::vector<CEntity*> _vecEntities);
	void ContainWanderSeparate(std::vector<CEntity*> _vecEntities);
	void ContainWanderAvoidObstacle(std::vector<CEntity*> _vecEntities);
	void ContainFollowLeader(CEntity _Leader, std::vector<CEntity*> _vecEntities);
	void ContainQueue(vec3 _target, std::vector<CEntity*> _vecEntities);

	void SetVelocity(vec3 _velocity);
	vec3 GetLocation();
	vec3 GetVelocity();
	void SetModelPosition();

	void Translate(vec3 delta);

	float GetHeight() const;
	float GetWidth() const;
	float GetDepth() const;

	void SetScale(vec3 _scale);

	Model* GetModel();

	bool IsHit() { return m_bIsHit; }
	void SetHit(bool b) { m_bIsHit = b; m_bFlagStateChange = true; }
	bool IsActive() { return m_bIsActive; }
	void SetActive(bool b) { m_bIsActive = b; m_bFlagStateChange = true; }

	void setMaxSpeed(float _maxSpeed);
	float getMaxSpeed();
	vec3 m_OldNetPos;
	bool m_bFlagStateChange = false; 

private:

	vec3 it(float _fMax, vec3 _vector);
	bool isOnLeaderSight(vec3 _LeaderPosition, vec3 _Ahead);
	CEntity* findMostThreateningObstacle(std::vector<CEntity*> _vecEntities, vec3 _ahead, vec3 _ahead2);
	bool lineIntersectsCircle(vec3 _ahead, vec3 _ahead2, CEntity* _Obstacle);
	CEntity* getNeighbourAhead(std::vector<CEntity*> _vecEntities);

protected:

	ModelType m_shape;
	char* m_strFilename;

	Model* m_model;

	vec3 m_location;
	vec3 m_velocity;
	vec3 m_acceleration;

	float m_fMaxforce;
	float m_fMaxspeed;

	bool m_bIsHit;
	bool m_bIsActive;
};

#endif 