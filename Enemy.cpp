#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

// getter for the tile
char Enemy::getTile() {
	return tile;
}

//Constructor to initialize enemy
Enemy::Enemy(string name, char tile, int level, int health, int attack, int defense, int expValue) {
	this->name = name;
	this->tile = tile;
	init(level, health, attack, defense);
	this->expValue = expValue;
}

// Takes damage while fighting with the character
int Enemy::takeDamage(int damage) {
	
		damage -= defense;
		if (damage > 0) {
			health -= damage;
			if (health <= 0) {
				//Enemy died
				return expValue;
			}
		}
		// Enemy not strong to hurt player | miss fire
		return 0;	
}

// Random movement or if the player nears, tries to catch him
int Enemy::getMove(int playerX, int playerY) {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 4); // I give 4 because I wanted to see the enemies that don't walk 50%  
	int distance = abs(playerX - xPos) + abs(playerY - yPos); // absolute distance between the enemy and the player
	int dx = xPos - playerX;
	int dy = yPos - playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	//Try to catch the player
	if (distance <= 5) {
		if (adx > ady) {
			//move on x-axis
			if (dx > 0) {
				return (int)'a';
			}
			else {
				return (int)'d';
			}
		}

	}

	//if distance is far, enemies walk randomly on the x-axis
	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return (int)'a';
		break;
	case 1:
		return (int)'d';
		break;
	}
}
