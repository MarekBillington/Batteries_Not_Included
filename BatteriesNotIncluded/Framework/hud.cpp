#include "hud.h"
#include "player.h"
#include "backbuffer.h"

Hud::Hud(Player* p)
{
	hu_player = p;
	mapType = true;
}

Hud::~Hud()
{
}


void
Hud::Process(float deltaTime)
{

}

void
Hud::Draw(BackBuffer& backBuffer)
{
	//get health, find how much is bar and how much is batteries
	int health = hu_player->getHealth();
	if (health > 0){
		int bar = health % 100;
		int numBatteries = (health - bar) / 100;
		if (bar == 0){
			numBatteries--;
			bar = 100;
		}


		//draw health bar
		backBuffer.SetDrawColour(255, 60, 60, 150);
		backBuffer.DrawRectangle(5, 5, 5 + (bar * 5), 25);

		//setup batteries
		while (numBatteries > hu_batteries.size()){
			Sprite* temp = backBuffer.CreateSprite("assets\\battery.png");
			backBuffer.SetSpriteAlpha(temp, 150);
			hu_batteries.push_back(temp);

		}
		//draw batteries
		for (int i = 0; i < numBatteries; i++){
			hu_batteries.at(i)->SetX(5 + (i * 27));
			hu_batteries.at(i)->SetY(35);
			backBuffer.DrawSpriteHUD((*hu_batteries.at(i)));

		}
	}

	//set up for both types of minimaps
	int roomX = hu_player->getCurrentRoomX();
	int roomY = hu_player->getCurrentRoomY();

	//Draw Basic MiniMap
	if (mapType){
		//mini-map whole thing
		for (int x = 1080; x <= 1260; x += 22){
			for (int y = 5; y <= 155; y += 18){
				if ((x - 1080) / 22 == roomX && (y - 5) / 18 == roomY)
					backBuffer.SetDrawColour(255, 255, 255, 150);
				else
					backBuffer.SetDrawColour(220, 220, 220, 150);
				backBuffer.DrawRectangle(x, y, x + 22, y + 18);
				backBuffer.SetDrawColour(0, 0, 0, 100);
				backBuffer.DrawRectangleOutline(x, y, x + 22, y + 18);
			}
		}

		//draw player icon
		backBuffer.SetDrawColour(60, 100, 255, 150);
		int miniPlayerX = ((hu_player->GetPositionX() - (hu_player->getCurrentRoomX() * 1280)) / 58) + (1080 + (22 * hu_player->getCurrentRoomX()));
		int miniPlayerY = ((hu_player->GetPositionY() - (hu_player->getCurrentRoomY() * 720)) / 40) + (5 + (18 * hu_player->getCurrentRoomY()));
		backBuffer.DrawRectangle(miniPlayerX, miniPlayerY, miniPlayerX + 2, miniPlayerY + 2);
	}




	//draw dyamnic minimap
	if (!mapType){
		//backBuffer.DrawRectangle(1080, 5, 1272, 113);
		for (int x = roomX - 1; x < roomX + 2; x++){
			for (int y = roomY - 1; y < roomY + 2; y++){
				//if(visted somehow){
				if (x >= 0 && y >= 0 && x < 9 && y < 9){
					int tempx = (((x - (roomX - 1)) * 64) + 1080);
					int tempy = (((y - (roomY - 1)) * 36) + 5);

					if (x == roomX && y == roomY)
						backBuffer.SetDrawColour(255, 255, 255, 150);
					else
						backBuffer.SetDrawColour(220, 220, 220, 150);
					backBuffer.DrawRectangle(tempx, tempy, tempx + 64, tempy + 36);
					backBuffer.SetDrawColour(0, 0, 0, 150);
					backBuffer.DrawRectangleOutline(tempx, tempy, tempx + 64, tempy + 36);
				}
			}
		}

		//draw player icon
		backBuffer.SetDrawColour(60, 100, 255, 100);
		int miniPlayerX = ((hu_player->GetPositionX() - (hu_player->getCurrentRoomX() * 1280)) / 20) + 1144;
		int miniPlayerY = ((hu_player->GetPositionY() - (hu_player->getCurrentRoomY() * 720)) / 20) + 41;
		backBuffer.DrawRectangle(miniPlayerX, miniPlayerY, miniPlayerX + 5, miniPlayerY + 5);
	}





	//draw weapon display
	//hu_player->getWeapon();


	// Draw passives
	/*
	hu_player->getPassive(1);
	hu_player->getPassive(2);
	hu_player->getPassive(3);
	hu_player->getPassive(4);
	*/


	//draw Active
	//hu_player->getActive();


	//get boss timer
	//backBuffer.drawText(bossTimer);

	//get item room timer
	//backBuffer.drawText(bossTimer);
}