#pragma once
#include <string>
#include "World.h"
using namespace std;

//directions of movement
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

//cases of collisions
#define EMPTY_CELL 1
#define THE_SAME_SPACIES 2
#define FIGHT 3
#define MEET_TURTLE 4
#define MEET_ANTELOPE 5
#define MEET_PLANT 6

//abstract class (base for Animal and Plant)
class Organism
{
protected:
	int strength;
	int initiative;
	int positionY, positionX;
	char gridPresentation;		//symbol which is printed on screen as a presentation of organism
	string organismName;
	int indexAge;				//index in array of pointers to organism in world class
	class World* world;
public:
	virtual void action() = 0;																		//basic behaviour of organism
	virtual void collision(int typeOfCollision, int newPositionY, int newPositionX) = 0;			//behaviour of organism in case of collision
	virtual void draw() = 0;																		//draw representation of organism
	virtual void addOrganism(class World* world, int positionY, int positionX) = 0;					//add organism to world

	int getStrength() {
		return strength;
	}
	int getInitiative() {
		return initiative;
	}
	int getPositionY() {
		return positionY;
	}
	int getPositionX() {
		return positionX;
	}
	int getIndexAge() {
		return indexAge;
	}
	string getOrganismName() {
		return organismName;
	}
	char getGridPresentation() {
		return gridPresentation;
	}
	void setPositionY(int position) {
		positionY = position;
	}
	void setPositionX(int position) {
		positionX = position;
	}
	void setIndexAge(int index) {
		indexAge = index;
	}
	void setStrength(int strength) {
		this->strength = strength;
	}
	void setInitiative(int initiative) {
		this->initiative = initiative;
	}
	void decrementIndex() {
		indexAge--;
	}
};

//definitions of below functions in Functions.cpp file

//newPositionInsideGrid function checks whether possible new coordinates are inside grid
bool newPositionInsideGrid(class World* world, int direction, int currentPositionY, int currentPositionX);

//newPositionInsideGridAntelope function checks whether possible new coordinates are inside grid (in movement by two fields)
bool newPositionInsideGrid2(class World* world, int direction, int currentPositionY, int currentPositionX);

//newPosition function establish new coordinates according to direction of movement
void newPosition(int direction, int* newPositionY, int* newPositionX);

//newPosition function establish new coordinates according to direction of movement by two fields
void newPosition2(int direction, int* newPositionY, int* newPositionX);

//spaceForNewAnimal function checks whether it is possibility to create new organism next to organism
//if one of the neighboring cells is empty, then function return true
bool spaceForNewAnimal(class World* world, int positionY, int positionX);

//spaceToMove function checks whether there is place to move for fox where is weaker organism than fox
bool spaceToMove(class World* world, int positionY, int positionX, int strength);
