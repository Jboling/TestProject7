#include "IUnit.hpp"

IUnit::IUnit() {
	this->zero();
	fCreationTime = CClock::instance()->getCurrentTime();
	this->type = "";

	fMaxVelocity = 8.0;
	fMaxAcceleration = 128.0;
	fFriction = 32.0;

	CEventManager::instance()->subscribe(this);
}

void IUnit::moment() {
	float fTimeStep = CClock::instance()->getTimeStep();

	float dist = glm::length(velocity);
	if (dist <= fFriction*fTimeStep) {
		velocity = glm::vec2(0.0, 0.0);
	}
	else {
		velocity -= glm::normalize(velocity) * (fFriction * fTimeStep);
	}

	velocity += acceleration * fTimeStep;

	dist = glm::length(velocity);
	if (dist > fMaxVelocity) {
		velocity = glm::normalize(velocity) * fMaxVelocity;
	}

	position += velocity * fTimeStep;
}

void IUnit::kill() {
	CEventManager::instance()->post(&IUnitEVENTDeath(this));
	delete this;
}

void IUnit::notify(IEvent *e) {
	if (e->compareType("event_iunit_kill")) {
		IUnitEVENTKill *request = (IUnitEVENTKill *)e;
		if (request->getUnit() == NULL || request->getUnit() == this) {
			kill();
		}
	}

	extendedNotify(e);
}