#include "CSession.hpp"
#include "CPlayer.hpp"

CSession::CSession() {
	eventManager = CEventManager::instance();
	sdlManager = CSDLManager::instance();

	iFrameDelay = 16;
	bRunning = true;

	map = new CMap();

	eventManager->subscribe(this);
}

void CSession::run() {
	CClock *clock = CClock::instance();
	CCamera *camera = CCamera::instance();
	CPlayer *player = new CPlayer();

	for (int i = -4; i <= 4; i++) {
		for (int j = -4; j <= 4; j++) {
			glm::vec2 position(i, j);
			if (glm::length(position) <= 4.2) {
				map->addMapChunk(i, j);
			}
		}
	}
	
	camera->setTarget(player);

	while (bRunning) {
		iFrameStart = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sdlManager->sdlEventHandle();

		clock->updateClock(iFrameDelay);
		player->update();

		camera->positionCamera();
		drawScene();
		player->draw();

		glFinish();
		sdlManager->swapBuffers();
		iFrameEnd = SDL_GetTicks();
		if (iFrameDelay - (iFrameEnd - iFrameStart) > 0) {
			SDL_Delay(iFrameDelay - (iFrameEnd - iFrameStart));
		}
		iFrameDelay = iFrameEnd - iFrameStart;
		iFrameDelay = iFrameDelay < 16 ? 16 : iFrameDelay;
	}
}

void CSession::drawScene() {
	map->draw();
}

void CSession::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_quit")) {
		bRunning = false;
	}
}