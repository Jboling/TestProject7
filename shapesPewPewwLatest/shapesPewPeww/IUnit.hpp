#ifndef _IUNIT_HPP
#define _IUNIT_HPP
#include "CEventManager.hpp"
#include "CGLBufferManager.hpp"
#include "CGLBuffer.hpp"
#include "CCamera.hpp"
#include "CLocation.hpp"
#include "CClock.hpp"
#include "main.hpp"

class IUnit : public CLocation, public IEventable {
protected:
	string type;

	CLocation lastLocation;
	float fCreationTime;

	float fMaxVelocity;
	float fMaxAcceleration;
	float fFriction;
	
public:
	IUnit();

	void moment();
	virtual void update() = 0;
	virtual void draw() = 0;

	void kill();

	string getType() { return type; }
	void setType(string type) { this->type = type; }

	void notify(IEvent *e);
	virtual void extendedNotify(IEvent *e) = 0;
};

class IUnitEVENTKill : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTKill(IUnit *unit) {
		this->type = "event_iunit_kill";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

class IUnitEVENTDeath : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTDeath(IUnit *unit) {
		this->type = "event_iunit_death";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

class IUnitEVENTUpdated : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTUpdated(IUnit *unit) {
		this->type = "event_iunit_updated";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

#endif /* !_IUNIT_HPP */