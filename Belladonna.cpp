#include "Plants.h"
#include <iostream>

using namespace std;

#define BELLADONNA_STRENGTH 99

Belladonna::Belladonna(class World* world, int positionY, int positionX, string plantType)
{
	this->strength = BELLADONNA_STRENGTH;
	this->initiative = PLANTS_INITIATIVE;
	this->organismName = plantType;
	this->gridPresentation = 'b';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Belladonna::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Belladonna::addOrganism(class World* world, int positionY, int positionX)
{
	Belladonna* tmp = new Belladonna(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}