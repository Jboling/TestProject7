#ifndef _CMAPCHUNK_HPP
#define _CMAPCHUNK_HPP
#include "CEventManager.hpp"
#include "CGLBufferManager.hpp"
#include "CGLBuffer.hpp"
#include "IUnit.hpp"
#include "main.hpp"

enum CMAPCHUNK_STATE {
	CMAPCHUNK_STATE_EXIST = 1,
	CMAPCHUNK_STATE_HASUP = 2,
	CMAPCHUNK_STATE_HASLEFT = 4,
	CMAPCHUNK_STATE_HASDOWN = 8,
	CMAPCHUNK_STATE_HASRIGHT = 16
};

class CMapChunk : public IEventable {
private:
	int iChunkX;
	int iChunkY;
	int iState;

	CGLBuffer *glBuffers[6];
	std::map<IUnit *, IUnit *> unitList;

public:
	CMapChunk(int iChunkX, int iChunkY);

	void addUnit(IUnit *unit);
	void remUnit(IUnit *unit);
	bool unitExist(IUnit *unit);
	std::map<IUnit *, IUnit *> *getUnitList() { return &unitList; }

	void setState(int iState) { this->iState = iState; }
	void addState(int iState) { this->iState |= iState; }
	void remState(int iState) { this->iState &= (~iState); }
	int getState() { return iState; }
	void draw();

	void notify(IEvent *e);
};

#endif /* !_CMAPCHUNK_HPP */