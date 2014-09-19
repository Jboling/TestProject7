#include "CLocation.hpp"

#ifndef M_PI
#define M_PI	(3.1415926535897932384626433832795)
#endif

CLocation::CLocation() {
	position = glm::vec2(0.0, 0.0);
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(10.0, 0.0);
	anglePos = 0.0;
	angleVel = 0.0;
	angleAcc = 0.0;
}

CLocation::CLocation(float xpos, float ypos) {
	position = glm::vec2(xpos, ypos);
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	anglePos = 0.0;
	angleVel = 0.0;
	angleAcc = 0.0;
}

CLocation::CLocation(glm::vec2 position) {
	this->position = position;
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	anglePos = 0.0;
	angleVel = 0.0;
	angleAcc = 0.0;
}

CLocation::CLocation(CLocation *location) {
	this->position = location->getPosition();
	this->velocity = location->getVelocity();
	this->acceleration = location->getAcceleration();
	this->anglePos = location->getAnglePos();
	this->angleVel = location->getAngleVel();
	this->angleAcc = location->getAngleAcc();
}

CLocation &CLocation::operator=(CLocation &location) {
	this->position = location.getPosition();
	this->velocity = location.getVelocity();
	this->acceleration = location.getAcceleration();
	this->anglePos = location.getAnglePos();
	this->angleVel = location.getAngleVel();
	this->angleAcc = location.getAngleAcc();
	return *this;
}