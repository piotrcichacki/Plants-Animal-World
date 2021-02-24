#include "Animals.h"
#include <iostream>

using namespace std;

#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4

Antelope::Antelope(class World* world, int positionY, int positionX, string animalName)
{
	this->strength = ANTELOPE_STRENGTH;
	this->initiative = ANTELOPE_INITIATIVE;
	this->organismName = animalName;
	this->gridPresentation = 'A';
	this->positionX = positionX;
	this->positionY = positionY;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Antelope::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Antelope::addOrganism(class World* world, int positionY, int positionX)
{
	Antelope* tmp = new Antelope(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

//wider range of movement - two fields instead of one
void Antelope::action()
{
	int direction = 0, rangeOfMovement = 1, typeOfCollision = 0;
	int newPositionY = positionY, newPositionX = positionX;
	int escapeFromFight = 0;
	bool freeNeighboringCell = false;
	bool positionInsideGrid = false;
	int freeCellPositionY, freeCellPositionX;

	do
	{
		direction = rand() % 4 + 1;
		rangeOfMovement = rand() % 2 + 1;					//antelope can move one or two field
		if (rangeOfMovement == 1)
		{
			positionInsideGrid = newPositionInsideGrid(world, direction, positionY, positionX);
		}
		else
		{
			positionInsideGrid = newPositionInsideGrid2(world, direction, positionY, positionX);
		}
	} while (!positionInsideGrid);

	if (rangeOfMovement == 1)
		newPosition(direction, &newPositionY, &newPositionX);
	else
		newPosition2(direction, &newPositionY, &newPositionX);

	//antelope has 50% chance to escape from fight with other animals
	if (world->grid[newPositionY][newPositionX] == 'W' && world->grid[newPositionY][newPositionX] == 'S' && world->grid[newPositionY][newPositionX] == 'F' && world->grid[newPositionY][newPositionX] == 'T')
	{
		escapeFromFight = rand() % 2;
	}

	if (escapeFromFight == 1)		//antelope escape
	{
		freeNeighboringCell = spaceForNewAnimal(world, newPositionY, newPositionX);
		if (!freeNeighboringCell)	//there is no free neighboring cell to escape
		{
			escapeFromFight = 0;
		}
		else
		{
			freeCellPositionY = newPositionY;
			freeCellPositionX = newPositionX;

			while (world->grid[freeCellPositionY][freeCellPositionX] != ' ')
			{
				freeCellPositionY = newPositionY;
				freeCellPositionX = newPositionX;

				do
				{
					direction = rand() % 4 + 1;
				} while (!newPositionInsideGrid(world, direction, newPositionY, newPositionX));

				newPosition(direction, &freeCellPositionY, &freeCellPositionX);
			}
			cout << organismName << " escaped from fight." << endl;
			collision(EMPTY_CELL, freeCellPositionY, freeCellPositionX);
		}

	}
	if (escapeFromFight == 0)					//antelope does not escape
	{
		if (world->grid[newPositionY][newPositionX] == ' ')
			typeOfCollision = EMPTY_CELL;
		else if (world->grid[newPositionY][newPositionX] == gridPresentation)
			typeOfCollision = THE_SAME_SPACIES;
		else if (world->grid[newPositionY][newPositionX] == 'T')
			typeOfCollision = MEET_TURTLE;
		else if (world->grid[newPositionY][newPositionX] == 's' || world->grid[newPositionY][newPositionX] == 't' || world->grid[newPositionY][newPositionX] == 'g' || world->grid[newPositionY][newPositionX] == 'b' || world->grid[newPositionY][newPositionX] == 'h')
			typeOfCollision = MEET_PLANT;
		else
			typeOfCollision = FIGHT;

		collision(typeOfCollision, newPositionY, newPositionX);
	}
}