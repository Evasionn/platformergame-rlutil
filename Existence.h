#pragma once
#include <random>
#include <ctime>
using namespace std;
class Existence
{
protected:
	int health; //Stores health of the object
	int defense; //Stores defense value of the object
	int level; //Stores level of the object 
	int attack; //Stores attack value of the object
	int xPos; //Stores position on the x-axis
	int yPos; //Stores position on the y-axis
public:
	Existence();
	~Existence();
	Existence(int, int, int, int); //Constructor
	void init(int, int, int, int); //Initialize the object
	void setPosition(int, int); //Setting xPos & yPos of the object
	void getPosition(int &, int &); //Getting xPos & yPos of the object
	int attacking(); // Randomly genareted value for attacking acording to the object's attack value
	virtual int takeDamage(int); // Virtual method for the objects
};

