#include "Plants.h"
#include <iostream>

using namespace std;

#define HOGWEED_STRENGTH 10

Hogweed::Hogweed(class World* world, int positionY, int positionX, string plantType)
{
	this->strength = HOGWEED_STRENGTH;
	this->initiative = PLANTS_INITIATIVE;
	this->organismName = plantType;
	this->gridPresentation = 'h';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Hogweed::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Hogweed::addOrganism(class World* world, int positionY, int positionX)
{
	Hogweed* tmp = new Hogweed(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

void Hogweed::action()
{
	int index;
	int newPositionY = positionY, newPositionX = positionX;
	bool killAnimal = false;

	for (int i = 1; i <= 4; i++)	//go through 4 neighboring cells (up, left, right, down)
	{
		newPositionY = positionY;
		newPositionX = positionX;
		index = 0;

		if (newPositionInsideGrid(world, i, positionY, positionX))
		{
			newPosition(i, &newPositionY, &newPositionX);
			if (world->grid[newPositionY][newPositionX] == 'W' || world->grid[newPositionY][newPositionX] == 'S' || world->grid[newPositionY][newPositionX] == 'F' || world->grid[newPositionY][newPositionX] == 'A' || world->grid[newPositionY][newPositionX] == 'T') //checks whether in neighboring cell is animal
			{
				index = world->findOrganism(newPositionY, newPositionX);
				cout << organismName << " killed " << world->organisms[index]->getOrganismName() << endl;
				world->grid[newPositionY][newPositionX] = ' ';
				world->deleteOrganism(index);
				killAnimal = true;
			}
		}
	}

	if (!killAnimal)
	{
		cout << organismName << " didn't kill any neighboring animal" << endl;
	}

	draw();
}