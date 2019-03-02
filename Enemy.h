#pragma once
#include <string>
#include "Existence.h"
using namespace std;
class Enemy : public Existence
{
private:
	int expValue; // Stores the experience value that gives the player after the enemy dies
	string name; // Enemy's name
	char tile; // Enemy's symbol on the map
public:
	Enemy();
	~Enemy();
	Enemy(string, char, int, int, int, int, int); //Constructor to initialize enemy
	int takeDamage(int); // Takes damage while fighting with the character
	int getMove(int,int); // Random movement or if the player nears, tries to catch him
	char getTile(); // getter for the tile
};

