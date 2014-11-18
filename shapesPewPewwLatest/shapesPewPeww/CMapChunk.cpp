#include "CMapChunk.hpp"

CMapChunk::CMapChunk(int iChunkX, int iChunkY) {
	CGLBufferManager *glBufferManager = CGLBufferManager::instance();

	this->iChunkX = iChunkX;
	this->iChunkY = iChunkY;
	iState = CMAPCHUNK_STATE_EXIST;

	glBuffers[0] = glBufferManager->get("buffer_minorgrid");
	glBuffers[1] = glBufferManager->get("buffer_majorgrid");
	glBuffers[2] = glBufferManager->get("buffer_wallup");
	glBuffers[3] = glBufferManager->get("buffer_wallleft");
	glBuffers[4] = glBufferManager->get("buffer_walldown");
	glBuffers[5] = glBufferManager->get("buffer_wallright");

	CEventManager::instance()->subscribe(this);
}

void CMapChunk::addUnit(IUnit *unit) {
	if (!unitExist(unit)) {
		unitList[unit] = unit;
	}
}

void CMapChunk::remUnit(IUnit *unit) {
	if (unitExist(unit)) {
		unitList.erase(unit);
	}
}

bool CMapChunk::unitExist(IUnit *unit) {
	if (unitList.count(unit) != 0) {
		return true;
	}
	return false;
}

void CMapChunk::draw() {
	glPushMatrix();
	glTranslatef((float)iChunkX*16.0, (float)iChunkY*16.0, 0.0);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			glPushMatrix();

			glTranslatef((float)i * 8.0, (float)j * 8.0, -9.9);
			glBuffers[0]->getGLShader()->setUniform3f("color3f", 0.1, 0.1, 0.1);
			glBuffers[0]->drawElements();

			glTranslatef(0.0, 0.0, 0.1);
			glBuffers[1]->getGLShader()->setUniform3f("color3f", 0.2, 0.2, 0.2);
			glBuffers[1]->drawElements();
			
			glPopMatrix();
		}
	}

	glTranslatef(0.0, 0.0, -9.7);
	if (!(iState & CMAPCHUNK_STATE_HASUP)) {
		glBuffers[2]->getGLShader()->setUniform3f("color3f", 1.0, 1.0, 1.0);
		glBuffers[2]->drawElements();
	}
	if (!(iState & CMAPCHUNK_STATE_HASLEFT)) {
		glBuffers[3]->getGLShader()->setUniform3f("color3f", 1.0, 1.0, 1.0);
		glBuffers[3]->drawElements();
	}
	if (!(iState & CMAPCHUNK_STATE_HASDOWN)) {
		glBuffers[4]->getGLShader()->setUniform3f("color3f", 1.0, 1.0, 1.0);
		glBuffers[4]->drawElements();
	}
	if (!(iState & CMAPCHUNK_STATE_HASRIGHT)) {
		glBuffers[5]->getGLShader()->setUniform3f("color3f", 1.0, 1.0, 1.0);
		glBuffers[5]->drawElements();
	}
	glPopMatrix();
}

void CMapChunk::notify(IEvent *e) {
	
}