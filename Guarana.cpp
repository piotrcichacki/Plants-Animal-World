#include "Plants.h"
#include <iostream>

using namespace std;

#define GUARANA_STRENGTH 0

Guarana::Guarana(class World* world, int positionY, int positionX, string plantType)
{
	this->strength = GUARANA_STRENGTH;
	this->initiative = PLANTS_INITIATIVE;
	this->organismName = plantType;
	this->gridPresentation = 'g';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Guarana::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Guarana::addOrganism(class World* world, int positionY, int positionX)
{
	Guarana* tmp = new Guarana(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}