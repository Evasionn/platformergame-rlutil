#pragma once
#include "rlutil.h"
#include "Existence.h"
class Player: public Existence
{
private:
	int lives; // Remaining lives
	int experience; // Experience
	int jumpCounter; // Jump counter to avoid flying character
public:
	Player();
	~Player();
	void init(int,int,int,int, int); // Initializing character values
	void addExp(int); // Gaining experience point
	int takeDamage(int); // Taking damage logic from enemies
	void printInfo(); // Printing info on the bottom of the screen

	int getHealth(); //  Return remeaning health point 
	void addHealth(int); // Gaining health as bonus
	int getJumpCounter(); // Returns jump counter
	void setJumpCounter(int); // Sets jump counter 

	void addAttack(int); // Gaining attack damage bonus
	void addDefense(int); // Gaining Defense bonus
	void addLife(); // Gaining life Bonus
	int getLeftLives(); // Returns remaning lives
	void decreaseLives(); // Decreases remaining lives after player dies
};

