#include "room.h"
#include "game.h"
#include "backbuffer.h"

Room::Room()
{
}

Room::Room(int i, int j, RoomType type)
	:ro_roomNumber(type)
{
	m_x = i * 1280;
	m_y = j * 720;
	//could probably do this above but eh

	createTerrain(type);
}

Room::~Room()
{
}




void
Room::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y)); 

	for (size_t i = 0; i < ro_terrainContainer.size(); i++)
	{
		//if (!ro_terrainContainer.at(i)->IsDead()){
			ro_terrainContainer.at(i)->Process(deltaTime);
		//}
	}

}

void
Room::Draw(BackBuffer& backBuffer)
{
	m_pSprite->Draw(backBuffer);

	for (size_t i = 0; i < ro_terrainContainer.size(); i++)
	{
		ro_terrainContainer.at(i)->Draw(backBuffer);
	}
}


bool 
Room::IsCollidingWith(Entity& e){

	//for players only this code is whack
	bool result = false;

	/*float terX = m_x;
	float terY = m_y;
	float entX = e.GetPositionX();
	float entY = e.GetPositionY();



	if (terX < entX && terX + 80 > entX && terY < entY && terY + 80 > entY)
	{
		Sprite* sprite = e.getSprite();
		int eWidth = sprite->GetWidth();
		int eHeight = sprite->GetHeight();

		result = true;
	}
	return result;*/

	for (size_t i = 0; i < ro_terrainContainer.size(); i++)
	{
		ro_terrainContainer.at(i)->IsCollidingWith(e);
		result = true;
	}
	return result;
}


void Room::setRoomNumber(RoomType num){
	ro_roomNumber = num;
}

int Room::getRoomNumber(){
	return ro_roomNumber;
}


void 
Room::createTerrain(RoomType type){

	Game& game = Game::GetGame();
	BackBuffer* backBuffer = game.CallBackBuffer();


	if (type == fourDoors){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Terrain* dwayneTheSpikeJohnson = new Terrain(SPIKE, m_x + 900, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson);

		Terrain* dwayneTheHoleJohnson = new Terrain(HOLE, m_x + 300, m_y + 520, backBuffer);
		ro_terrainContainer.push_back(dwayneTheHoleJohnson);



	}
	else if (type == threeDoorsTopWall){

	}
	else if (type == threeDoorsBottomWall){

	}
	else if (type == threeDoorsLeftWall){

	}
	else if (type == threeDoorsRightWall){

	}
	else if (type == twoDoorsTopLeftWalls){

	}
	else if (type == twoDoorsTopRightWalls){

	}
	else if (type == twoDoorsBottomLeftWalls){

	}
	else if (type == twoDoorsBottomRightWalls){

	}
	else if (type == twoDoorsSplitHorizontal){

	}
	else if (type == twoDoorsSplitVertical){

	}
	else if (type == oneDoorAtBottom){

	}
	else if (type == oneDoorAtTop){

	}
	else if (type == oneDoorOnRight){

	}
	else if (type == oneDoorOnLeft){

	}
		

}