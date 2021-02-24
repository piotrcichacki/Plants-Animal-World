#include "Plants.h"
#include <iostream>

using namespace std;

#define GRASS_STRENGTH 0

Grass::Grass(class World* world, int positionY, int positionX, string plantType)
{
	this->strength = GRASS_STRENGTH;
	this->initiative = PLANTS_INITIATIVE;
	this->organismName = plantType;
	this->gridPresentation = 's';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Grass::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Grass::addOrganism(class World* world, int positionY, int positionX)
{
	Grass* tmp = new Grass(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}