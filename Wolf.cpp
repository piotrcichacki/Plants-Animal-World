#include "Animals.h"
#include <iostream>

using namespace std;

#define WOLF_STRENGTH 9
#define WOLF_INITIATIVE 5

Wolf::Wolf(class World* world, int positionY, int positionX, string animalName)
{
	this->strength = WOLF_STRENGTH;
	this->initiative = WOLF_INITIATIVE;
	this->organismName = animalName;
	this->gridPresentation = 'W';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Wolf::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Wolf::addOrganism(class World* world, int positionY, int positionX)
{
	Wolf* tmp = new Wolf(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}
