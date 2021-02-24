#include "Animals.h"
#include "World.h"
#include <iostream>

using namespace std;

#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1

Turtle::Turtle(class World* world, int positionY, int positionX, string animalName)
{
	this->strength = TURTLE_STRENGTH;
	this->initiative = TURTLE_INITIATIVE;
	this->organismName = animalName;
	this->gridPresentation = 'T';
	this->positionX = positionX;
	this->positionY = positionY;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Turtle::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Turtle::addOrganism(class World* world, int positionY, int positionX)
{
	Turtle* tmp = new Turtle(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

//has 75% to stay in the same place
void Turtle::action()
{
	int stayInTheSamePlace;
	int direction = 0, typeOfCollision = 0;
	int newPositionY = positionY, newPositionX = positionX;

	stayInTheSamePlace = rand() % 4;	//randomize whether turtle perform move or not

	if (stayInTheSamePlace == 0)		//turtle perform move (one of four possible values = 25%)
	{
		do
		{
			direction = rand() % 4 + 1;
		} while (!newPositionInsideGrid(world, direction, positionY, positionX));

		newPosition(direction, &newPositionY, &newPositionX);

		if (world->grid[newPositionY][newPositionX] == ' ')
			typeOfCollision = EMPTY_CELL;
		else if (world->grid[newPositionY][newPositionX] == gridPresentation)
			typeOfCollision = THE_SAME_SPACIES;
		else if (world->grid[newPositionY][newPositionX] == 'A')
			typeOfCollision = MEET_ANTELOPE;
		else if (world->grid[newPositionY][newPositionX] == 's' || world->grid[newPositionY][newPositionX] == 't' || world->grid[newPositionY][newPositionX] == 'g' || world->grid[newPositionY][newPositionX] == 'b' || world->grid[newPositionY][newPositionX] == 'h')
			typeOfCollision = MEET_PLANT;
		else
			typeOfCollision = FIGHT;

		collision(typeOfCollision, newPositionY, newPositionX);
	}
	else
	{
		cout << organismName << " was to lazy to move and stayed on the same position." << endl;
		draw();
	}

}