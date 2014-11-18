#include "CCamera.hpp"

CCamera::CCamera() {
	target = NULL;
	fCameraOffset = 0.2;

	iWindowWidth = 800;
	iWindowHeight = 600;

	clock = CClock::instance();
	CEventManager::instance()->subscribe(this);
}

bool CCamera::setTarget(CLocation *target) {
	if (target) {
		this->target = target;
		return true;
	}
	return false;
}

bool CCamera::hasValidTarget() {
	if (target) {
		return true;
	}
	return false;
}

bool CCamera::positionCamera() {
	float fCameraWidth = getCameraWidth();
	float fCameraHeight = getCameraHeight();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, iWindowWidth, iWindowHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fCameraWidth / 2.0, fCameraWidth / 2.0, -fCameraHeight / 2.0, fCameraHeight / 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (target) {
		glTranslatef(0.0, -fCameraHeight * fCameraOffset, 0.0);
		glRotatef(target->angle.x, 0.0, 0.0, 1.0);
		glTranslatef(-target->position.x, -target->position.y, 0.0);
		return true;
	}

	return false;
}

void CCamera::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_windoweventresize")) {
		CSDLManagerEVENTWindowEventResize *request = (CSDLManagerEVENTWindowEventResize *)e;
		iWindowWidth = request->getWidth();
		iWindowHeight = request->getHeight();
	}
}

CCamera *CCamera::instance() {
	static CCamera *inst = NULL;
	if (!inst) {
		inst = new CCamera();
	}
	return inst;
}