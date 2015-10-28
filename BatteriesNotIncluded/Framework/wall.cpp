#include "wall.h"


Wall::Wall(int x, int y, int width, int height, Side side)
	: wa_xloc(x)
	, wa_yloc(y)
	, wa_width(width)
	, wa_height(height)
	, wa_side(side)
{
}

Wall::~Wall()
{
}



bool
Wall::IsCollidingWith(Entity& e)
{
	bool result = false;

	int eWidth = e.getWidth();
	int eHeight = e.getHeight() / 2;
	int entityX = e.GetPositionX();
	int entityY = e.GetPositionY() + eHeight;



	if (wa_xloc + wa_width <= entityX || wa_xloc >= entityX + eWidth){
		return false;
	}
	if (wa_yloc + wa_height <= entityY || wa_yloc >= entityY + eHeight){
		return false;
	}


	if (wa_side == TOP || wa_side == BOTTOM){
		if (wa_yloc <= entityY + eHeight && wa_yloc + 50 >= entityY + eHeight){
			//north, blocks moving down
			e.SetPositionY(wa_yloc - ((eHeight * 2) + 1));
		}
		else if (wa_yloc + (wa_height - 50) <= entityY && wa_yloc + wa_height >= entityY){ //done
			//south, blocks moving up
			e.SetPositionY(wa_yloc + 41);
		}
		else if (wa_xloc <= entityX + eWidth  && wa_xloc + 50 >= entityX + eWidth){ //done
			//west, blocks moveing right
			e.SetPositionX(wa_xloc - (eWidth + 1));
		}
		else if (wa_xloc + (wa_width - 50) <= entityX  && wa_xloc + wa_width >= entityX){ //done
			//east, blocks moving left
			e.SetPositionX(wa_xloc + 151);
		}
	}
	else{
		
		if (wa_xloc <= entityX + eWidth  && wa_xloc + 50 >= entityX + eWidth){ //done
			//west, blocks moveing right
			e.SetPositionX(wa_xloc - (eWidth + 1));
		}
		else if (wa_xloc + (wa_width - 50) <= entityX  && wa_xloc + wa_width >= entityX){ //done
			//east, blocks moving left
			e.SetPositionX(wa_xloc + 151);
		}
		else if (wa_yloc <= entityY + eHeight && wa_yloc + 50 >= entityY + eHeight){
			//north, blocks moving down
			e.SetPositionY(wa_yloc - ((eHeight * 2) + 1));
		}
		else if (wa_yloc + (wa_height - 50) <= entityY && wa_yloc + wa_height >= entityY){ //done
			//south, blocks moving up
			e.SetPositionY(wa_yloc + 41);
		}
		
	}

	



	result = true;
	
	return result;
}


int 
Wall::getX(){
	return wa_xloc;
}

int 
Wall::getY(){
	return wa_yloc;
}

int 
Wall::getWidth(){
	return wa_width;
}

int 
Wall::getHeight(){
	return wa_height;
}