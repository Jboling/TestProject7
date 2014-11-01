#include "CCamera.hpp"

CCamera::CCamera() {
	target = NULL;
	fRotation = 0.0;
	fRotationSpeed = 180.0;
	fCameraOffset = 0.0;

	iWindowWidth = 800;
	iWindowHeight = 600;

	clock = CClock::instance();
	CEventManager::instance()->subscribe(this);
}

bool CCamera::setTarget(CLocation *location) {
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
	float fTimeStep = clock->getTimeStep();
	float fCameraWidth = getCameraWidth();
	float fCameraHeight = getCameraHeight();

	if (iCameraKeys & CCAMERA_KEYS_LEFT) { fRotation -= fRotationSpeed*fTimeStep; }
	if (iCameraKeys & CCAMERA_KEYS_RIGHT) { fRotation += fRotationSpeed*fTimeStep; }

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fCameraWidth / 2.0, fCameraWidth / 2.0, -fCameraHeight / 2.0, fCameraHeight / 2.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (target) {
		glTranslatef(target->position.x, target->position.y, 0.0);
		glRotatef(fRotation, 0.0, 0.0, 1.0);
		return true;
	}

	return false;
}

void CCamera::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_keydown")) {
		CSDLManagerEVENTKeyDown *request = (CSDLManagerEVENTKeyDown *)e;
		iCameraKeys |= request->getKey() == SDLK_q ? CCAMERA_KEYS_LEFT : 0;
		iCameraKeys |= request->getKey() == SDLK_e ? CCAMERA_KEYS_RIGHT : 0;
	}
	else if (e->compareType("event_sdlmanager_keyup")) {
		CSDLManagerEVENTKeyUp *request = (CSDLManagerEVENTKeyUp *)e;
		iCameraKeys &= ~(request->getKey() == SDLK_q ? CCAMERA_KEYS_LEFT : 0);
		iCameraKeys &= ~(request->getKey() == SDLK_e ? CCAMERA_KEYS_RIGHT : 0);
	}
	else if (e->compareType("event_sdlmanager_windoweventresize")) {
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