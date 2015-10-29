#include "room.h"
#include "game.h"
#include "backbuffer.h"

Room::Room()
{
}

Room::Room(int i, int j, RoomType type, RoomSpecial special)
	:ro_roomNumber(type)
	, ro_roomSpecial(special)
{
	m_x = i * 1280;
	m_y = j * 720;
	//could probably do this above but eh

	createTerrain(type);

	//topwall
	createWall(m_x + 0, m_y + 0, 570, 93, TOP, false, false);
	if (!ro_doorNorth){
		createWall(m_x + 570, m_y + 0, 130, 93, TOP, true, false);
	}
	else{
		createWall(m_x + 570, m_y + 0, 130, 93, TOP, true, true);
	}
		createWall(m_x + 710, m_y + 0, 570, 93, TOP, false, false);
	
	//rightwall
		createWall(m_x + 1129, m_y + 0, 151, 331, RIGHT, false, false);
	if (!ro_doorEast){
		createWall(m_x + 1129, m_y + 301, 151, 117, RIGHT, true, false);
	}
	else{
		createWall(m_x + 1129, m_y + 301, 151, 117, RIGHT, true, true);
	}
		createWall(m_x + 1129, m_y + 418, 151, 302, RIGHT, false, false);

	//bottomwall
		createWall(m_x + 0, m_y + 625, 570, 160, BOTTOM, false, false);
	if (!ro_doorSouth){
		createWall(m_x + 570, m_y + 625, 130, 160, BOTTOM, true, false);
	}
	else{
		createWall(m_x + 570, m_y + 625, 130, 160, BOTTOM, true, true);
	}
		createWall(m_x + 710, m_y + 625, 570, 160, BOTTOM, false, false);

	//leftwall
		createWall(m_x + 0, m_y + 0, 151, 331, LEFT, false, false);
	if (!ro_doorWest){
		createWall(m_x + 0, m_y + 301, 151, 117, LEFT, true, false);
	}
	else{
		createWall(m_x + 0, m_y + 301, 151, 117, LEFT, true, true);
	}
		createWall(m_x + 0, m_y + 418, 151, 302, LEFT, false, false);

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

	for (size_t i = 0; i < ro_enemyContainer.size(); i++)
	{
		//if (!ro_terrainContainer.at(i)->IsDead()){
		ro_enemyContainer.at(i)->Process(deltaTime);
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

	for (size_t i = 0; i < ro_enemyContainer.size(); i++)
	{
		ro_enemyContainer.at(i)->Draw(backBuffer);
	}
}


bool 
Room::IsCollidingWith(Entity& e){

	bool result = false;
	/////////////////////////////////////

	for (size_t i = 0; i < ro_wallContainer.size(); i++)
	{
		ro_wallContainer.at(i)->IsCollidingWith(e);
		result = true;
	}

	///////////////////////////////////////
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


		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == threeDoorsTopWall){



		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == threeDoorsBottomWall){

		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = true;
	}
	else if (type == threeDoorsLeftWall){

		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == threeDoorsRightWall){

		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == twoDoorsTopLeftWalls){
		//test
		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == twoDoorsTopRightWalls){

		ro_doorNorth = false;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == twoDoorsBottomLeftWalls){

		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
	else if (type == twoDoorsBottomRightWalls){

		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = false;
		ro_doorWest = true;
	}
	else if (type == twoDoorsSplitHorizontal){
		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = true;
		
	}
	else if (type == twoDoorsSplitVertical){

		

		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == oneDoorAtBottom){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);


		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);

		ro_doorNorth = false;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == oneDoorAtTop){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);

		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
	else if (type == oneDoorOnRight){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);

		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
	else if (type == oneDoorOnLeft){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);

		ro_doorNorth = false;
		ro_doorEast = false;
		ro_doorSouth = false;
		ro_doorWest = true;
	}
	else{
		ro_doorNorth = false;
		ro_doorEast = false;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
		

}

RoomType
Room::getRoomType(){
	return ro_roomNumber;
}

RoomSpecial
Room::getRoomSpecial(){
	return ro_roomSpecial;
}


void 
Room::createWall(int x, int y, int width, int height, Side side, bool door, bool open){
	Wall* wall = new Wall(x, y, width, height, side, door, open);
	ro_wallContainer.push_back(wall);
}