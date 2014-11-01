#include "IUnit.hpp"

IUnit::IUnit() {
	name = "unit_default";
	type = "iunit";

	glBuffer = CGLBufferManager::instance()->get("buffer_default");
	// glBuffer = NULL;
	fCreateTime = CClock::instance()->getCurrentTime();
	bAllowSuicide = true;

	CEventManager::instance()->subscribe(this);
}

IUnit::~IUnit() {
	// We do not need to post a death event if we just want to delete.
	// Only post on a proper kill call.
	CEventManager::instance()->unsubscribe(this);
}

void IUnit::loadUnitJson(string name) {
	// Overwrite me.
}

void IUnit::update() {
	float fTimeStep = CClock::instance()->getTimeStep();

	velocity += acceleration * fTimeStep;
	position += velocity * fTimeStep;
}

void IUnit::draw() {
	if (glBuffer) {
		glBuffer->drawElements();
	}
}

bool IUnit::compareType(string type) {
	if (this->type.compare(type) == 0) {
		return true;
	}
	return false;
}

bool IUnit::compareName(string name) {
	if (this->name.compare(name) == 0) {
		return true;
	}
	return false;
}

void IUnit::kill() {
	CEventManager *eventManager = CEventManager::instance();

	eventManager->unsubscribe(this);
	// We can still post events after we unsubscribe.
	// We do not want this unit to respond to chain reaction events.
	eventManager->post(new IUnitEVENTDeath(this));

	// Commit suicide? Yes please
	if (bAllowSuicide) {
		delete this;
	}
}

void IUnit::allowSuicide(bool bAllow) {
	this->bAllowSuicide = bAllow;
}

void IUnit::notify(IEvent *e) {
	if (e->compareType("event_iunit_kill")) {
		IUnitEVENTKill *request = (IUnitEVENTKill *)e;
		IUnit *unit = request->getUnit();
		if (unit) {
			if (unit == this) {
				kill();
			}
		}
		else {
			// NULL? Apply to all units.
			kill();
		}
	}
	else if (e->compareType("event_iunit_update")) {
		IUnitEVENTUpdate *request = (IUnitEVENTUpdate *)e;
		IUnit *unit = request->getUnit();
		if (unit) {
			if (unit == this) {
				update();
			}
		}
		else {
			// NULL? Apply to all units.
			update();
		}
	}
	else if (e->compareType("event_iunit_draw")) {
		IUnitEVENTDraw *request = (IUnitEVENTDraw *)e;
		IUnit *unit = request->getUnit();
		if (unit) {
			if (unit == this) {
				draw();
			}
		}
		else {
			// NULL? Apply to all units.
			draw();
		}
	}
	else if (e->compareType("event_iunit_updateadndraw")) {
		IUnitEVENTDraw *request = (IUnitEVENTDraw *)e;
		IUnit *unit = request->getUnit();
		if (unit) {
			if (unit == this) {
				update();
				draw();
			}
		}
		else {
			// NULL? Apply to all units.
			update();
			draw();
		}
	}

	extendedNotify(e);
}

void IUnit::extendedNotify(IEvent *e) {
	// Overwrite me.
}