#pragma once
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CGLManager.hpp"

class CSession : public IEventable {
private:
	CEventManager *eventManager = CEventManager::instance();
	CSDLManager *sdlManager = CSDLManager::instance();
	CGLManager *glManager = CGLManager::instance();

	float orthoWidth;
	float orthoHeight;

	bool running;
	int fstart;
	int fend;
	int fdelay;

public:
	CSession();

	void glSetup();
	void run();
	void drawScene();

	float getOrthoWidth() { return orthoWidth; }
	float getOrthoHeight() { return orthoHeight; }

	void notify(IEvent *e);
};