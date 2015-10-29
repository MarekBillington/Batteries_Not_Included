// 717310 C++ SDL Framework
#ifndef __HUD_H__
#define __HUD_H__

#include <string>
#include <vector>
#include "sprite.h"

class Player;
class BackBuffer;

class Hud
{
public:
	Hud(Player* p);
	~Hud();

	void Process(float deltatime);
	void Draw(BackBuffer& backBuffer, int minutesToBoss, int secondsToBoss);

	//something to update current item room
	//something for boss timer

	//spirtes
	//Sprite* hu_healthBar;

	bool mapType;


private:
	std::vector<Sprite*> hu_batteries;
	Player* hu_player;

};
#endif // __HUD_H__

