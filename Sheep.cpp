#include "Animals.h"
#include "World.h"
#include <iostream>

using namespace std;

#define SHEEP_STRENGTH 4
#define SHEEP_INITIATIVE 4

Sheep::Sheep(class World* world, int positionY, int positionX, string animalName)
{
	this->strength = SHEEP_STRENGTH;
	this->initiative = SHEEP_INITIATIVE;
	this->organismName = animalName;
	this->gridPresentation = 'S';
	this->positionX = positionX;
	this->positionY = positionY;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Sheep::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Sheep::addOrganism(class World* world, int positionY, int positionX)
{
	Sheep* tmp = new Sheep(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}
