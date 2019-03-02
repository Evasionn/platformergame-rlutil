#include "Existence.h"



Existence::Existence()
{
}


Existence::~Existence()
{
}

//Constructor
Existence::Existence(int level, int health, int attack, int defense) {
	this->health = health;
	this->attack = attack;
	this->defense = defense;
	this->level = level;
}

//Initialize the object
void Existence::init(int level, int health, int attack, int defense) {
	this->health = health;
	this->attack = attack;
	this->defense = defense;
	this->level = level;
}

//Setting xPos & yPos of the object
void Existence::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

//Getting xPos & yPos of the object
void Existence::getPosition(int & x, int & y) {
	x = xPos;
	y = yPos;
}

// Randomly genareted value for attacking acording to the object's attack value
int Existence::attacking() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, attack);
	return attackRoll(randomEngine); 
}

// Virtual method for the objects
int Existence::takeDamage(int damage) {
	return 0;
}