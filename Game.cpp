#include "Game.h"

Game::Game()
{
	// SETTING WINDOW SIZE
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left,0, 800, 600, TRUE); // 800 width, 600 height

	playing = false;
	rows = rlutil::trows()-1;
	cols = rlutil::tcols()-1;

	rlutil::setConsoleTitle(GameName);
	rlutil::hidecursor();
	
}


Game::~Game()
{
}


//Main menu screen
int Game::mainMenu() {
	rlutil::setBackgroundColor(9);
	rlutil::setColor(14);
	gotoxy(cols / 2 - 7, rows / 2 - 9);
	cout << GameName << endl;
	gotoxy(cols / 2 - 4, rows / 2 - 8);
	cout << "MAIN MENU" << endl;
	gotoxy(cols / 2 - 5, rows / 2 - 5);
	cout << "F2: New Game" << endl;
	gotoxy(cols / 2 - 5, rows / 2 - 4);
	cout << "F3: Quit";

	rlutil::setBackgroundColor(4);
	gotoxy(4, rows - 2);
	cout << "Choose a menu item";


	// MENU ANIMATION
	int x = 2, y = 2, switcher = 1;
	while (true) {
		rlutil::setColor(0);
		rlutil::setBackgroundColor(15);
		if (switcher != 9) {
			gotoxy(x, y);
			cout << "#";
			switch (switcher) {
			case 1:
				if (x == cols) switcher++;
				else x++;
				break;
			case 2:
				if (y == rows) switcher++;
				else y++;
				break;
			case 3:
				if (x == 2) switcher++;
				else x--;
				break;
			case 4:
				if (y == 2) switcher++;
				else y--;
				break;
			case 5:
				y = 3;
				if (x == cols) switcher++;
				else x++;
				break;
			case 6:
				x = cols - 1;
				if (y == rows) switcher++;
				else y++;
				break;
			case 7:
				y = rows - 1;
				if (x == 2) switcher++;
				else x--;
				break;
			case 8:
				x = 3;
				if (y == 2) switcher++;
				else y--;
				break;
			}
		}


		//READING KEY INPUT
		//F2 for new game
		//F3 for quit
		if(kbhit()){
			int key = rlutil::getkey();
			if (key == rlutil::KEY_F2 || key == rlutil::KEY_F3) return key;
			cout.flush();
		}
		rlutil::msleep(10);
	}
}

//Create new game
void Game::newGame() {
	rlutil::resetColor();
	rlutil::setBackgroundColor(0);
	rlutil::cls();
	playing = true;
	player.init(1,100,10,5,0);
	level.loadLevel("level_1.txt", player);
	level.printMap();
	player.printInfo();
}

//First screen of the console {MAIN MENU}
void Game::run() {
	int key;
	if (playing == false) {
		key = mainMenu();
		if (key == rlutil::KEY_F2) {
			newGame();
			playGame();
		}
	}
}

//Main looper of the game screen
void Game::playGame() {
	
	while (playing != false) {
		level.updateEnemies(player);
		level.printMap();
		player.printInfo();
		if (kbhit()) {
			int key = rlutil::getkey();
			level.movePlayer(player, key);
			cout.flush();
		}
		//adding gravity to our game engine
		level.movePlayer(player, rlutil::KEY_DOWN);
		rlutil::msleep(20);
		

		//Check the game is finished or not
		if (player.getLeftLives() <= 0) {
			rlutil::cls();
			gotoxy(cols / 2 - 4, rows / 2 - 8);
			rlutil::setColor(4);
			rlutil::setBackgroundColor(0);

			cout << "GAME OVER!" << endl << endl;
			playing =  false;
		}
		}
}
