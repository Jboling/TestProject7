#ifndef _CSESSION_HPP
#define _CSESSION_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CGLBufferManager.hpp"
#include "CGLBuffer.hpp"
#include "CMap.hpp"
#include "CCamera.hpp"
#include "CClock.hpp"
#include "main.hpp"

class CSession : public IEventable {
private:
	CEventManager *eventManager;
	CSDLManager *sdlManager;

	CMap *map;
	
	int iFrameStart;
	int iFrameEnd;
	int iFrameDelay;

	bool bRunning;

public:
	CSession();

	void run();
	void drawScene();

	void notify(IEvent *e);
};

#endif /* !_CSESSION_HPP */