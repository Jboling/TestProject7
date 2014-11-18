#ifndef _CMAP_HPP
#define _CMAP_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CMapChunk.hpp"
#include "main.hpp"

class CMap : public IEventable {
private:
	std::map<int, CMapChunk *> mapChunks;
	
	int getKey(int iChunkX, int iChunkY);

public:
	CMap();

	void addMapChunk(int iChunkX, int iChunkY);
	void remMapChunk(int iChunkX, int iChunkY);

	CMapChunk *getMapChunk(int iChunkX, int iChunkY);
	bool mapChunkExist(int iChunkX, int iChunkY);
	void fixChunkBorder(int iChunkX, int iChunkY);

	void update();
	void draw();

	void notify(IEvent *e);
};

#endif /* !_CMAP_HPP */