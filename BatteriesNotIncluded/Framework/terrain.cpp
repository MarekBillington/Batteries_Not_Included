#include "terrain.h"


Terrain::Terrain(TerrainType terr, int x, int y)
	:te_terrain(terr)
{
	SetPositionX(x);
	SetPositionY(y);
}

Terrain::~Terrain()
{
}


bool 
Terrain::IsCollidingWith(Entity& e){
	bool result = false;

	float terX = m_x;
	float terY = m_y;
	float entX = e.GetPositionX();
	float entY = e.GetPositionY();

	

	if (terX < entX && terX + 80 > entX && terY < entY && terY + 80 > entY)
	{
		Sprite* sprite = e.getSprite();
		int eWidth = sprite->GetWidth();
		int eHeight = sprite->GetHeight();
		
		if (te_terrain == SPIKE){
			
		}
		else if (te_terrain == HOLE){
			if (terY < entY + eHeight && terY + 30 > entY + eHeight){
				//north
				e.SetPositionY(terY - 20);
			}
			else if (terX + 50 < entX  && terX + 80 > entX){
				//east
				e.SetPositionX(terX + 100);
			}
			else if (terY + 50 < entY && terY + 80 > entY){
				//south
				e.SetPositionY(terY + 100);
			}
			else if (terX < entX + eWidth  && terX + 30 > entX + eWidth){
				//west
				e.SetPositionY(terX - 20);
			}

		}
		else if (te_terrain == ROCK){
			if (terY < entY + eHeight && terY + 30 > entY + eHeight){
				//north
				e.SetPositionY(terY - 20);
			}
			else if (terX + 50 < entX  && terX + 80 > entX){
				//east
				e.SetPositionX(terX + 100);
			}
			else if (terY + 50 < entY && terY + 80 > entY){
				//south
				e.SetPositionY(terY + 100);
			}
			else if (terX < entX + eWidth  && terX + 30 > entX + eWidth){
				//west
				e.SetPositionY(terX - 20);
				
			}
		}
		else{

		}


		
		result = true;
	}
	return result;
}

