#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "entity.h"
#include "sprite.h"

enum TerrainType
{
	HOLE,
	ROCK,
	SPIKE
};


class Terrain : public Entity
{
public:
	Terrain(TerrainType terrain, int x, int y);
	~Terrain();

	bool IsCollidingWith(Entity& e);
	

private:
	TerrainType te_terrain;
};


#endif // !__TERRAIN_H__
