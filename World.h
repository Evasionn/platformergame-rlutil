#pragma once
#include "rlutil.h"
#include <vector>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
//CONSTANT SYMBOLS ON THE MAP
#define PlayerSymbol '@'
#define AttackBonus 10
#define HealthBonus 25
#define DefenseBonus 5
#define Snake 'S'
#define Bandit 'B'
#define Wolf 'W'
#define Thief 'T'
#define Dragon 'D'
#define HealthSymbol '+'
#define LifeSymbol '*'
#define AttackSymbol '&'
#define DefenseSymbol '%'
#define Obstacle '#'
#define Trap '_'
#define Spike '|'
#define Movable ' '

using namespace std;
class World
{
private:
	vector <string> map; //The vector that is loaded with the tiles on the txt file
	vector <Enemy> enemies; //The vector that stores enemies on the map
	void processPlayerMove(Player &, int, int); //Logical operations about the movement of the character
	bool processEnemyMove(Player &, int, int, int); //Logical operations about the movement of the enemies
	void battleWithMonster(Player &, int, int); //Logical operations about fighting with the enemies
	int initialX; //Stores the initial x position of the player for reset game operation
	int initialY; //Stores the initial y position of the player for reset game operation
	void resetGame(Player &); //Reset game after player dies
public:
	World();
	~World();
	void loadLevel(string, Player&); // Loads the map from the txt file
	void printMap(); // Printing the vector named map
	void movePlayer(Player&, int); // Moves the player according to caught keys
	char getTile(int, int); // A method that gives wanted column's character
	void setTile(int, int, char); // A method that sets a column with a character
	void updateEnemies(Player&); // Looper for enemy movement
	void endGame(); // Ends the game after dragon has been slayed
};

