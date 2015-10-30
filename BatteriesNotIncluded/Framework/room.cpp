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
	ro_lockedSprite->SetX(static_cast<int>(m_x));
	ro_lockedSprite->SetY(static_cast<int>(m_y));


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
	if (ro_Locked == false){
		m_pSprite->Draw(backBuffer);
	}
	else {
		ro_lockedSprite->Draw(backBuffer);
	}

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
		if (ro_wallContainer.at(i)->IsCollidingWith(e, ro_Locked))
		{
			result = true;
		}
	}

	///////////////////////////////////////
	for (size_t i = 0; i < ro_terrainContainer.size(); i++)
	{
		if(ro_terrainContainer.at(i)->IsCollidingWith(e))
		{
			result = true;
		}
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



		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);
		Terrain* dwayneTheRockJohnson2 = new Terrain(ROCK, m_x + 520, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson2);
		Terrain* dwayneTheRockJohnson3 = new Terrain(ROCK, m_x + 680, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson3);


		Terrain* dwayneTheSpikeJohnson = new Terrain(SPIKE, m_x + 760, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson);
		Terrain* dwayneTheSpikeJohnson1 = new Terrain(SPIKE, m_x + 760, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson1);
		Terrain* dwayneTheSpikeJohnson2 = new Terrain(SPIKE, m_x + 440, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson2);
		Terrain* dwayneTheSpikeJohnson3 = new Terrain(SPIKE, m_x + 440, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson3);



		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == threeDoorsTopWall){

		Terrain* dwayneTheSpikeJohnson4 = new Terrain(SPIKE, m_x + 600, m_y + 200, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson4);
		Terrain* dwayneTheSpikeJohnson5 = new Terrain(SPIKE, m_x + 600, m_y + 440, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson5);
		Terrain* dwayneTheSpikeJohnson6 = new Terrain(SPIKE, m_x + 840, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson6);
		Terrain* dwayneTheSpikeJohnson7 = new Terrain(SPIKE, m_x + 360, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson7);


		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = true;
	}
	else if (type == threeDoorsBottomWall){

		Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Terrain* dwayneTheRockJohnson2 = new Terrain(ROCK, m_x + 520, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson2);

		Terrain* dwayneTheRockJohnson3 = new Terrain(ROCK, m_x + 680, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson3);


		Terrain* dwayneTheRockJohnson4 = new Terrain(ROCK, m_x + 600, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson4);
		Terrain* dwayneTheRockJohnson5 = new Terrain(ROCK, m_x + 520, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson5);
		Terrain* dwayneTheRockJohnson6 = new Terrain(ROCK, m_x + 680, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson6);

		Terrain* dwayneTheRockJohnson7 = new Terrain(ROCK, m_x + 520, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson7);
		Terrain* dwayneTheRockJohnson8 = new Terrain(ROCK, m_x + 680, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson8);


		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = true;
	}
	else if (type == threeDoorsLeftWall){


		Terrain* dwayneTheSpikeJohnson = new Terrain(SPIKE, m_x + 760, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson);
		Terrain* dwayneTheSpikeJohnson1 = new Terrain(SPIKE, m_x + 760, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson1);
		Terrain* dwayneTheSpikeJohnson2 = new Terrain(SPIKE, m_x + 440, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson2);
		Terrain* dwayneTheSpikeJohnson3 = new Terrain(SPIKE, m_x + 440, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson3);


		Terrain* dwayneTheSpikeJohnson4 = new Terrain(SPIKE, m_x + 840, m_y + 180, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson4);
		Terrain* dwayneTheSpikeJohnson5 = new Terrain(SPIKE, m_x + 840, m_y + 480, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson5);
		Terrain* dwayneTheSpikeJohnson6 = new Terrain(SPIKE, m_x + 360, m_y + 180, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson6);
		Terrain* dwayneTheSpikeJohnson7 = new Terrain(SPIKE, m_x + 360, m_y + 480, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson7);


		ro_doorNorth = true;
		ro_doorEast = true;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == threeDoorsRightWall){


		Terrain* dwayneTheSpikeJohnson4 = new Terrain(SPIKE, m_x + 840, m_y + 180, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson4);
		Terrain* dwayneTheSpikeJohnson5 = new Terrain(SPIKE, m_x + 840, m_y + 480, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson5);
		Terrain* dwayneTheSpikeJohnson6 = new Terrain(SPIKE, m_x + 360, m_y + 180, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson6);
		Terrain* dwayneTheSpikeJohnson7 = new Terrain(SPIKE, m_x + 360, m_y + 480, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson7);

		Terrain* dwayneTheHoleJohnson = new Terrain(SPIKE, m_x + 600, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheHoleJohnson);

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

		/*Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 560, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Terrain* dwayneTheSpikeJohnson = new Terrain(SPIKE, m_x + 860, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson);

		Terrain* dwayneTheHoleJohnson = new Terrain(HOLE, m_x + 300, m_y + 520, backBuffer);
		ro_terrainContainer.push_back(dwayneTheHoleJohnson);*/

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

		/*Terrain* dwayneTheHoleJohnson = new Terrain(HOLE, m_x + 600, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheHoleJohnson);

		Terrain* dwayneTheRockJohnson2 = new Terrain(ROCK, m_x + 600, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson2);
		Terrain* dwayneTheRockJohnson3 = new Terrain(ROCK, m_x + 600, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson3);*/

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

		Terrain* dwayneTheHoleJohnson = new Terrain(HOLE, m_x + 600, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheHoleJohnson);

		Terrain* dwayneTheRockJohnson2 = new Terrain(ROCK, m_x + 600, m_y + 240, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson2);
		Terrain* dwayneTheRockJohnson3 = new Terrain(ROCK, m_x + 600, m_y + 400, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson3);

		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == oneDoorAtBottom){

		/*Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);


		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);

		Terrain* dwayneTheSpikeJohnson = new Terrain(SPIKE, m_x + 900, m_y + 320, backBuffer);
		ro_terrainContainer.push_back(dwayneTheSpikeJohnson);*/
		if (m_x / 1280 == 4 && m_y / 720 == 3) {
			Enemy* theHoOfHoes = new Enemy(BOSS, m_x + 400, m_y + 10, backBuffer);
			ro_enemyContainer.push_back(theHoOfHoes);
		}

		ro_doorNorth = false;
		ro_doorEast = false;
		ro_doorSouth = true;
		ro_doorWest = false;
	}
	else if (type == oneDoorAtTop){

		/*Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);*/


		ro_doorNorth = true;
		ro_doorEast = false;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
	else if (type == oneDoorOnRight){

		/*Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);*/

		ro_doorNorth = false;
		ro_doorEast = true;
		ro_doorSouth = false;
		ro_doorWest = false;
	}
	else if (type == oneDoorOnLeft){

		/*Terrain* dwayneTheRockJohnson = new Terrain(ROCK, m_x + 600, m_y + 220, backBuffer);
		ro_terrainContainer.push_back(dwayneTheRockJohnson);

		Enemy* theHoOfHoes = new Enemy(ROBORAT, m_x + 400, m_y + 300, backBuffer);
		ro_enemyContainer.push_back(theHoOfHoes);*/

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

Enemy*
Room::getBoss(){
	Enemy* toReturn;
	for (size_t i = 0; i < ro_enemyContainer.size(); i++)
	{
		//if (!ro_terrainContainer.at(i)->IsDead()){
		if (ro_enemyContainer.at(i)->en_enemyType == BOSS){
			toReturn = ro_enemyContainer.at(i);
		}
		//}
	}
	return toReturn;
}