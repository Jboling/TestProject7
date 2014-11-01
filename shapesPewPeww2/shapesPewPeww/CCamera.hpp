#ifndef _CCAMERA_HPP
#define _CCAMERA_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CLocation.hpp"
#include "CClock.hpp"
#include "main.hpp"

enum CCAMERA_KEYS {
	CCAMERA_KEYS_LEFT = 0x01,
	CCAMERA_KEYS_RIGHT = 0x02
};

class CCamera : public IEventable {
private:
	CLocation *target;
	float fRotation;
	float fRotationSpeed;
	float fCameraOffset;
	int iCameraKeys;

	int iWindowWidth;
	int iWindowHeight;
	// Convinience pointer.
	CClock *clock;

	CCamera();

public:
	bool setTarget(CLocation *target);
	bool hasValidTarget();
	bool positionCamera();

	void setRotation(float fRotation) { this->fRotation = fRotation; }
	float getRotation() { return fRotation; }
	void setRotationSpeed(float fRotationSpeed) { this->fRotationSpeed = fRotationSpeed; }
	float getRotationSpeed() { return fRotationSpeed; }
	void setCameraOffset(float fCameraOffset) { this->fCameraOffset = fCameraOffset; }
	float getCameraOffset() { return fCameraOffset; }

	float getCameraWidth() { return (float)iWindowWidth / 16.0; }
	float getCameraHeight() { return (float)iWindowHeight / 16.0; }

	void notify(IEvent *e);
	static CCamera *instance();
};

#endif /* !_CCAMERA_HPP */