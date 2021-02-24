#include "Animals.h"
#include <iostream>

using namespace std;

#define FOX_STRENGTH 3
#define FOX_INITIATIVE 7

Fox::Fox(class World* world, int positionY, int positionX, string animalName)
{
	this->strength = FOX_STRENGTH;
	this->initiative = FOX_INITIATIVE;
	this->organismName = animalName;
	this->gridPresentation = 'F';
	this->positionX = positionX;
	this->positionY = positionY;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Fox::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Fox::addOrganism(class World* world, int positionY, int positionX)
{
	Fox* tmp = new Fox(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

//fox will never move to a cell occupied by a stronger organism
void Fox::action()
{
	int direction = 0, typeOfCollision = 0;
	int newPositionY = positionY, newPositionX = positionX;
	int index, enemyStrength;

	if (spaceToMove(world, positionY, positionX, strength))			//check if in one of the neighboring cells is weaker organism or is empty
	{
		do															//looking for empty cell or cell occupied by weaker organism
		{
			newPositionY = positionY;
			newPositionX = positionX;
			do
			{
				direction = rand() % 4 + 1;
			} while (!newPositionInsideGrid(world, direction, positionY, positionX));

			newPosition(direction, &newPositionY, &newPositionX);

			if (world->grid[newPositionY][newPositionX] == ' ')
				enemyStrength = 0;
			else
			{
				index = world->findOrganism(newPositionY, newPositionX);
				enemyStrength = world->organisms[index]->getStrength();
			}
		} while (strength < enemyStrength);


		if (world->grid[newPositionY][newPositionX] == ' ')
			typeOfCollision = EMPTY_CELL;
		else if (world->grid[newPositionY][newPositionX] == gridPresentation)
			typeOfCollision = THE_SAME_SPACIES;
		else if (world->grid[newPositionY][newPositionX] == 'T')
			typeOfCollision = MEET_TURTLE;
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
		cout << organismName << " sensed stronger organisms next to him and stayed on the same position." << endl;
		draw();
	}
}