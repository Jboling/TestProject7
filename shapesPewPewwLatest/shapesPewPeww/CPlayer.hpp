#ifndef _CPLAYER_HPP
#define _CPLAYER_HPP
#include "CEventManager.hpp"
#include "CGLBufferManager.hpp"
#include "CGLBuffer.hpp"
#include "CCamera.hpp"
#include "CLocation.hpp"
#include "CClock.hpp"
#include "IUnit.hpp"
#include "main.hpp"

enum CPLAYER_KEYS {
	CPLAYER_KEYS_UP = 1,
	CPLAYER_KEYS_LEFT = 2,
	CPLAYER_KEYS_DOWN = 4,
	CPLAYER_KEYS_RIGHT = 8,
	CPLAYER_KEYS_ROTATELEFT = 16,
	CPLAYER_KEYS_ROTATERIGHT = 32
};

class CPlayer : public IUnit {
private:
	CGLBuffer *glBuffer;
	int iHealth;
	int iKeys;

	float fRotationSpeed;

public:
	CPlayer();
	CPlayer(float xpos, float ypos);

	void update();
	void draw();

	void extendedNotify(IEvent *e);
};

#endif /* !_CPLAYER_HPP */