#pragma once
#include "rlutil.h"
#define GameName "Platformer v1.0"
#include "Player.h"
#include "World.h"
#include <vector>
using namespace std;
class Game
{
private:
	bool playing; // Stores the game is running or finished
	int rows; // Row number on the console screen
	int cols; // Column number on the console screen
	Player player; // Main player object
	World level; // Stores the map that will be loaded
public:
	Game();
	~Game();
	int mainMenu(); // Printing main menu and returns selected menu item
	void newGame(); // Creates new game
	void run(); // First method to call menu and others
	void playGame(); // Main looper of the game screen
};
