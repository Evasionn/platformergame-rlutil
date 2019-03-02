#include "Player.h"


Player::Player()
{
	this->lives = 3;
}


Player::~Player()
{
}

// Initializing character values
void Player::init(int level, int health, int attack, int defense, int experience) {
	Existence::init(level, health, attack, defense);
	this->experience = experience;
}

// Gaining experience point
void Player::addExp(int xp) {
	experience += xp;
	//level up on every 80 point
	while (experience >= 80) {
		experience -= 80;
		attack += 10;
		defense += 5;
		health += 10;
		level++;
	}
}

// Taking damage logic from enemies
int Player::takeDamage(int damage){
	//Reducing damage according to the player's defense
	damage -= defense;
	if (damage > 0) {
		health -= damage;
		if (health <= 0) {
			//Player died
			return 1;
		}
	}
	return 0;
}

// Printing info on the bottom of the screen
void Player::printInfo() {
	rlutil::setColor(4);
	gotoxy(2, 35);
	cout << "Lives: " << lives << "\t Health: " << health << "\t Level: "<< level << "\t XP: " << experience;
}

//  Return remeaning health point 
int Player::getHealth() {
	return health;
}

// Gaining health as bonus
void Player::addHealth(int health) {
	this->health += health;
	//Maximum health point must be 100
	if (this->health > 100) this->health = 100;
}

// Sets jump counter 
void Player::setJumpCounter(int counter) {
	jumpCounter = counter;
}

// Returns jump counter
int Player::getJumpCounter() {
	return jumpCounter;
}

void Player::addAttack(int attack) {
	this->attack += attack;
}

void Player::addDefense(int defense) {
	this->defense += defense;
}

void Player::addLife() {
	this->lives++;
}

int Player::getLeftLives() {
	return lives;
}

void Player::decreaseLives() {
	health = 100;
	lives--;
}