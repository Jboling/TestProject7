#ifndef _IUNIT_HPP
#define _IUNIT_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CGLBufferManager.hpp"
#include "CCamera.hpp"
#include "CLocation.hpp"
#include "CGLBuffer.hpp"

// This object can commit suicide!
// Be sure to always dynamically allocate units, or set 'allowSuicide()' to 'false'!
// If 'false' creator will be expected to deallocate.
class IUnit : public IEventable, public CLocation {
private:
	string name;
	string type;

	CGLBuffer *glBuffer;
	float fCreateTime;
	bool bAllowSuicide;

	glm::vec2 lastPosition;

public:
	IUnit();
	~IUnit();

	void loadUnitJson(string name);

	void update();
	void draw();

	float getCreateTime() { return fCreateTime; }
	float getExistTime() { return CClock::instance()->getCurrentTime() - fCreateTime; }

	bool compareType(string type);
	bool compareName(string name);

	// You will never guess what this one does.
	void kill();
	void allowSuicide(bool bAllow);
	void notify(IEvent *e);
	void extendedNotify(IEvent *e);
};

// Request to kill the given unit. NULL kills ALL units!
class IUnitEVENTKill : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTKill(IUnit *unit) {
		type = "event_iunit_kill";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

// Notifies others of a unit death. Only the afflicted unit should post this event.
class IUnitEVENTDeath : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTDeath(IUnit *unit) {
		type = "event_iunit_death";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

// Request a unit to update. NULL updates all units.
class IUnitEVENTUpdate : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTUpdate(IUnit *unit) {
		type = "event_iunit_update";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

// Request a unit to draw itself. NULL draws all units.
class IUnitEVENTDraw : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTDraw(IUnit *unit) {
		type = "event_iunit_draw";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

// Unused.
// Request a unit to update and draw itself. NULL applies to all units.
class IUnitEVENTUpdateAndDraw : public IEvent {
private:
	IUnit *unit;
public:
	IUnitEVENTUpdateAndDraw() {
		type = "event_iunit_updateanddraw";
		this->unit = unit;
	}
	IUnit *getUnit() { return unit; }
};

#endif /* !_IUNIT_HPP */