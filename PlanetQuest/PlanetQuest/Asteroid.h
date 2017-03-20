#include "Entity.h"
#include <math.h>


class Asteroid : public CEntity
{
public:
	Asteroid();
	~Asteroid();

	glm::vec3 GetPointOnCircle(float radius);
};



Asteroid::Asteroid()
{
	glm::vec3 SpawnPos = GetPointOnCircle(10);
	glm::vec3 Target = GetPointOnCircle(5);
	m_velocity = glm::normalize(Target - SpawnPos);
}

Asteroid::~Asteroid()
{

}


glm::vec3 Asteroid::GetPointOnCircle(float Radius)
{
	float x = Radius * cos(Radius);
	float z = Radius * sin(Radius);

	return glm::vec3(x, 0, z);
}

