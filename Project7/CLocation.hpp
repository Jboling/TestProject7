#pragma once
#include "main.hpp"

class CLocation {
private:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float anglePos;
	float angleVel;
	float angleAcc;

public:
	CLocation();
	CLocation(float xpos, float ypos);
	CLocation(glm::vec2 position);
	CLocation(CLocation *location);

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	void setPosition(glm::vec2 position) { this->position = position; }
	void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }
	void setVelocity(glm::vec2 velocity) { this->velocity = velocity; }
	void setAcceleration(float x, float y) { acceleration.x = x; acceleration.y = y; }
	void setAcceleration(glm::vec2 acceleration) { this->acceleration = acceleration; }
	void setAnglePos(float x);
	void setAngleVel(float x);
	void setAngleAcc(float x);
	
	glm::vec2 getPosition() { return position; }
	glm::vec2 getVelocity() { return velocity; }
	glm::vec2 getAcceleration() { return acceleration; }
	float getAnglePos() { return anglePos; }
	float getAngleVel() { return angleVel; }
	float getAngleAcc() { return angleAcc; }

	CLocation &operator=(CLocation &location);
};