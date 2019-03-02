#include "World.h"



World::World()
{
}

World::~World()
{
}

// Loads the map from the txt file
void World::loadLevel(string fileName, Player &player) {
	ifstream file;
	file.open(fileName);

	string line;
	while (getline(file, line)) {
		map.push_back(line);
	}
	file.close();

	//processing level
	char tile;
	for (int i = 0; i < static_cast<int>(map.size()); i++) {
		for (int j = 0; j < static_cast<int>(map[i].size()); j++) {
			tile = map[i][j];
			switch (tile) {
			case PlayerSymbol:
				//Player
				player.setPosition(j, i);
				initialX = j;
				initialY = i;
				break;
			case Snake:
				//Snake
				enemies.push_back(Enemy("Snake", tile, 1, 10,10,2,20));
				enemies.back().setPosition(j, i);
				break;
			case Bandit:
				//Bandit
				enemies.push_back(Enemy("Bandit", tile, 2, 35, 12, 5, 30));
				enemies.back().setPosition(j, i);
				break;
			case Wolf:
				//Wolf
				enemies.push_back(Enemy("Wolf", tile, 3, 50, 18, 7, 40));
				enemies.back().setPosition(j, i);
				break;
			case Thief:
				//Thief
				enemies.push_back(Enemy("Thief", tile, 4, 70, 21, 10, 60));
				enemies.back().setPosition(j, i);
				break;
			case Dragon:
				//Dragon
				enemies.push_back(Enemy("Dragon", tile, 99, 1500, 100, 60, 9999));
				enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}

// Printing the vector named map
void World::printMap() {
	rlutil::setColor(3);
	rlutil::setBackgroundColor(0);
	int k = 0; // To colorize
	for (int i = 0; i < static_cast<int>(map.size()); i++) {
		rlutil::setColor(k % 15 + 1);
		gotoxy(2, i + 1);
		cout << map[i].c_str() << endl;
		k++;
	}
}

// Moves the player according to caught keys
void World::movePlayer(Player &player, int key) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	switch (key) {
	case rlutil::KEY_UP:
	case (int)'w':
		if(player.getJumpCounter() < 2){
		processPlayerMove(player, playerX, playerY - 1);
		player.getPosition(playerX, playerY);
		processPlayerMove(player, playerX, playerY - 1);
		player.getPosition(playerX, playerY);
		processPlayerMove(player, playerX, playerY - 1);
		player.setJumpCounter(2);
		}
		//double processing for jump effect
		break;
	case rlutil::KEY_DOWN:
	case (int)'s':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case rlutil::KEY_LEFT:
	case (int)'a':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case rlutil::KEY_RIGHT:
	case (int)'d':
		processPlayerMove(player, playerX + 1, playerY);
		break;
		//CHEAT AREA
		//Pressing 'h' for full health
	case (int)'h':
		player.addHealth(100);
		break;
		//Pressing 'l' for extra life
	case (int)'l':
		player.addLife();
		break;
		//Pressing 'p' for attack bonus
	case (int)'p':
		player.addAttack(AttackBonus);
		break;
		//Pressing 'b' for defense bonus
	case (int)'b':
		player.addDefense(DefenseBonus);
		break;
	}
}

// Gives wanted column's character
char World::getTile(int x, int y) {
	return map[y][x];
}

// Sets a column with a character
void World::setTile(int x, int y, char tile) {
	map[y][x] = tile;
}

//Logical operations about the movement of the character
void World::processPlayerMove(Player & player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case HealthSymbol:
		//Taking health bonus
		player.addHealth(HealthBonus);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, PlayerSymbol);
			break;
	case AttackSymbol:
		//Taking bonus attack
		player.addAttack(AttackBonus);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, PlayerSymbol);
		break;
	case DefenseSymbol:
		//Taking bonus defense
		player.addDefense(DefenseBonus);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, PlayerSymbol);
		break;
	case LifeSymbol:
		//Taking bonus life
		player.addLife();
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, PlayerSymbol);
		break;
	case Obstacle:
		//There is obstacle
		player.setJumpCounter(0);
		break;
	case Movable:
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, PlayerSymbol);
		break;
	case Snake:
	case Bandit:
	case Wolf:
	case Thief:
	case Dragon:
		//battle with enemies
	battleWithMonster(player, targetX, targetY);
		break;
	case Trap:
	case Spike:
		//Dies after meeting with trap or spike
		resetGame(player);
		setTile(playerX, playerY, ' ');
		printMap();
		break;

	}
}

//Logical operations about fighting with the enemies
void World::battleWithMonster(Player & player, int targetX, int targetY) {
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int result;
	player.getPosition(playerX, playerY);
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].getPosition(enemyX, enemyY);
		
		if (targetX == enemyX && targetY == enemyY) {
			// Player turn
			attackRoll = player.attacking();
			result = enemies[i].takeDamage(attackRoll);
			if (result != 0) {
				//enemy died
				setTile(targetX, targetY, ' ');
				printMap();
				player.addExp(result);
				player.printInfo();
				
				//If the dragon slayed
				if (enemies[i].getTile() == Dragon) {
					endGame();
				}
				
				//removing enemy from the vector

				enemies[i] = enemies.back();
				enemies.pop_back();
				return;
			}

			//Monster Turn
			attackRoll = enemies[i].attacking();
			gotoxy(2, 36);
			result = player.takeDamage(attackRoll);

			if (result == 1) {
				//Player died
				//restart game and reduce live
				setTile(playerX, playerY, ' ');
				resetGame(player);
				printMap();
				
			}
		}
	}

	player.printInfo();
}

// Looper for enemy movement
void World::updateEnemies(Player & player) {
	int playerX, playerY, enemyX, enemyY;
	player.getPosition(playerX, playerY);
	int aiMove;
	bool died = false;
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].getPosition(enemyX, enemyY);
		aiMove = enemies[i].getMove(playerX, playerY); //random movement or trying to catch player
		switch (aiMove) {
		case rlutil::KEY_UP:
		case (int)'w':
			died = processEnemyMove(player,i, enemyX, enemyY - 1);
			break;
		case rlutil::KEY_DOWN:
		case (int)'s':
			died = processEnemyMove(player,i, enemyX, enemyY + 1);
			break;
		case rlutil::KEY_LEFT:
		case (int)'a':
			died = processEnemyMove(player,i, enemyX - 1, enemyY);
			break;
		case rlutil::KEY_RIGHT:
		case (int)'d':
			died = processEnemyMove(player,i, enemyX + 1, enemyY);
			
			break;
		}
		if (died) i--;
		//Gravity effect
		processEnemyMove(player, i, enemyX, enemyY + 1);
	}
}


//Logical operations about the movement of the enemies
bool World::processEnemyMove(Player & player, int enemyIndex, int targetX, int targetY) {
	if (enemyIndex >= enemies.size()) return false;

	int playerX, playerY, enemyX, enemyY;
	enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case Obstacle:
		//There is obstacle
		break;
	case Trap:
	case Spike:
		//remove enemy
		setTile(enemyX, enemyY, ' ');
		enemies[enemyIndex] = enemies.back();
		enemies.pop_back();
		printMap();
		return true;
		break;
	case Movable:
		//Can move
		enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, ' ');
		setTile(targetX, targetY, enemies[enemyIndex].getTile());
		
		break;
	case PlayerSymbol:
		//Fight with the player
		battleWithMonster(player, enemyX, enemyY);
		break;
	}
	return false;
}

//Reset game after player dies
void World::resetGame(Player & player) {
	player.decreaseLives();
	player.setPosition(initialX, initialY);
}

// Ends the game after dragon has been slayed
void World::endGame() {
	rlutil::cls();
	gotoxy(94 / 2 - 22, 9);
	rlutil::setColor(2);
	rlutil::setBackgroundColor(0);

	cout << "You've slayed the dragon and saved the earth!" << endl << endl;

	exit(0);
}