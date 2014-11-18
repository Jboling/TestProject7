#ifndef _CCAMERA_HPP
#define _CCAMERA_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CLocation.hpp"
#include "CClock.hpp"
#include "CCamera.hpp"
#include "main.hpp"

class CCamera : public IEventable {
private:
	CLocation *target;
	float fCameraOffset;
	int iCameraKeys;

	int iWindowWidth;
	int iWindowHeight;
	// Convinience pointers.
	CClock *clock;

	CCamera();

public:
	bool setTarget(CLocation *target);
	bool hasValidTarget();
	bool positionCamera();

	void setCameraOffset(float fCameraOffset) { this->fCameraOffset = fCameraOffset; }
	float getCameraOffset() { return fCameraOffset; }

	float getCameraWidth() { return (float)iWindowWidth / 16.0; }
	float getCameraHeight() { return (float)iWindowHeight / 16.0; }

	void notify(IEvent *e);
	static CCamera *instance();
};

#endif /* !_CCAMERA_HPP */