#include "CSession.hpp"

CSession::CSession() {
	running = true;
	fdelay = 16;

	orthoWidth = 800.0 / 8.0;
	orthoHeight = 600.0 / 8.0;
	glSetup();

	eventManager->subscribe(this);
}

void CSession::glSetup() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, orthoWidth*8.0, orthoHeight*8.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-orthoWidth/2.0, orthoWidth/2.0, -orthoHeight/2.0, orthoHeight/2.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CSession::run() {
	while (running) {
		fstart = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sdlManager->sdlEventHandle();

		glLoadIdentity();
		drawScene();

		glFlush();
		sdlManager->swapBuffers();
		fend = SDL_GetTicks();
		if (fend - fstart < fdelay) { SDL_Delay(fdelay - (fend - fstart)); }
		fdelay = fend - fstart;
		fdelay = fdelay<16 ? 16 : fdelay;
	}
}

void CSession::drawScene() {

}

void CSession::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_quit")) {
		running = false;
	}
}