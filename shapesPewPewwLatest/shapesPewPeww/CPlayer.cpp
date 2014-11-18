#include "CPlayer.hpp"

CPlayer::CPlayer() {
	glBuffer = CGLBufferManager::instance()->get("buffer_tripsquare");
	iHealth = 100;
	iKeys = 0;

	fMaxVelocity = 24.0;
	fMaxAcceleration = 128.0;
	fFriction = 32.0;

	fRotationSpeed = 180.0;
}

CPlayer::CPlayer(float xpos, float ypos) {
	glBuffer = CGLBufferManager::instance()->get("buffer_tripsquare");
	iHealth = 100;

	fMaxVelocity = 24.0;
	fMaxAcceleration = 128.0;
	fFriction = 32.0;

	fRotationSpeed = 180.0;

	position.x = xpos;
	position.y = ypos;
}

void CPlayer::update() {
	float fTimeStep = CClock::instance()->getTimeStep();
	glm::vec2 direction = glm::vec2(0.0, 0.0);

	if (iKeys & CPLAYER_KEYS_UP) { direction.y += 1.0; }
	if (iKeys & CPLAYER_KEYS_LEFT) { direction.x -= 1.0; }
	if (iKeys & CPLAYER_KEYS_DOWN) { direction.y -= 1.0; }
	if (iKeys & CPLAYER_KEYS_RIGHT) { direction.x += 1.0; }

	if (iKeys & CPLAYER_KEYS_ROTATELEFT) { angle.x -= fRotationSpeed*fTimeStep; }
	if (iKeys & CPLAYER_KEYS_ROTATERIGHT) { angle.x += fRotationSpeed*fTimeStep; }

	float r = angle.x * (M_PI / 180.0);
	glm::mat2 rotationMatrix(cos(r), -sin(r), sin(r), cos(r));
	direction = rotationMatrix*direction;

	if (glm::length(direction) > 1.0) {
		direction = glm::normalize(direction);
	}
	acceleration = direction * fMaxAcceleration;

	this->moment();
}

void CPlayer::draw() {
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glBuffer->getGLShader()->setUniform3f("color3f", 0.3, 1.0, 0.3);
	glBuffer->drawElements();
	glPopMatrix();
}

void CPlayer::extendedNotify(IEvent *e) {
	if (e->compareType("event_sdlmanager_keydown")) {
		CSDLManagerEVENTKeyDown *request = (CSDLManagerEVENTKeyDown *)e;
		iKeys |= (request->getKey() == SDLK_w ? CPLAYER_KEYS_UP : 0);
		iKeys |= (request->getKey() == SDLK_a ? CPLAYER_KEYS_LEFT : 0);
		iKeys |= (request->getKey() == SDLK_s ? CPLAYER_KEYS_DOWN : 0);
		iKeys |= (request->getKey() == SDLK_d ? CPLAYER_KEYS_RIGHT : 0);
		iKeys |= (request->getKey() == SDLK_q ? CPLAYER_KEYS_ROTATELEFT : 0);
		iKeys |= (request->getKey() == SDLK_e ? CPLAYER_KEYS_ROTATERIGHT : 0);
	}
	else if (e->compareType("event_sdlmanager_keyup")) {
		CSDLManagerEVENTKeyUp *request = (CSDLManagerEVENTKeyUp *)e;
		iKeys &= ~(request->getKey() == SDLK_w ? CPLAYER_KEYS_UP : 0);
		iKeys &= ~(request->getKey() == SDLK_a ? CPLAYER_KEYS_LEFT : 0);
		iKeys &= ~(request->getKey() == SDLK_s ? CPLAYER_KEYS_DOWN : 0);
		iKeys &= ~(request->getKey() == SDLK_d ? CPLAYER_KEYS_RIGHT : 0);
		iKeys &= ~(request->getKey() == SDLK_q ? CPLAYER_KEYS_ROTATELEFT : 0);
		iKeys &= ~(request->getKey() == SDLK_e ? CPLAYER_KEYS_ROTATERIGHT : 0);
	}
}