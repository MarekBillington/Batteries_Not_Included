#include "terrain.h"
#include "backbuffer.h"

Terrain::Terrain(TerrainType terr, int x, int y, BackBuffer* backBuffer)
	:te_terrain(terr)
{
	SetPositionX(x);
	SetPositionY(y);

	Sprite* terrainSprite;
		
	if (terr == ROCK){
		terrainSprite = backBuffer->CreateSprite("assets\\block80.png");
	}
	else if (terr == SPIKE){
		terrainSprite = backBuffer->CreateSprite("assets\\spikes80.png");
	}
	else if (terr == HOLE){
		terrainSprite = backBuffer->CreateSprite("assets\\hole80.png");
	}
	
	Initialise(terrainSprite);
	
}

Terrain::~Terrain()
{
}


bool 
Terrain::IsCollidingWith(Entity& e){
	bool result = false;

	int eWidth;
	int eHeight;

	
	eWidth = e.getWidth();
	eHeight = e.getHeight() / 2;
	float terX = m_x;
	float terY = m_y;
	float entX = e.GetPositionX()/* + (eWidth /2)*/;
	float entY = e.GetPositionY() + eHeight;




	int terWidth = m_pSprite->GetWidth();
	int terHeight = m_pSprite->GetHeight();

	if (terX + terWidth < entX || terX > entX + eWidth){
		return false;
	}
	if (terY + terHeight < entY || terY > entY + eHeight){
		return false;
	}

		
	if (te_terrain == SPIKE){
		e.setHealth(e.getHealth()-5);
	}
	else if (te_terrain == HOLE){
		if (terY < entY + eHeight && terY + 30 > entY + eHeight){
			//north
			e.SetPositionY(terY - ((eHeight * 2) + 1));
		}
		else if (terX + 50 < entX  && terX + 80 > entX){
			//east
			e.SetPositionX(terX + 81);
		}
		else if (terY + 50 < entY && terY + 80 > entY){
			//south
			e.SetPositionY(terY + 25);
		}
		else if (terX < entX + eWidth  && terX + 30 > entX + eWidth){
			//west
			e.SetPositionX(terX - (eWidth + 1));
		}

	}
	else if (te_terrain == ROCK){
		if (terY < entY + eHeight && terY + 30 > entY + eHeight){
			//north
			e.SetPositionY(terY - ((eHeight * 2) + 1));
		}
		else if (terX + 50 < entX  && terX + 80 > entX){
			//east
			e.SetPositionX(terX + 81);
		}
		else if (terY + 50 < entY && terY + 80 > entY){
			//south
			e.SetPositionY(terY + 25);
		}
		else if (terX < entX + eWidth  && terX + 30 > entX + eWidth){
			//west
			e.SetPositionX(terX - (eWidth + 1));
		}
	}
	else{

	}


		
		result = true;
	/*}*/
	return result;
}

