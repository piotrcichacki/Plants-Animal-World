#include "Plants.h"
#include <iostream>

using namespace std;

#define SOW_STRENGTH 0

SowThistle::SowThistle(class World* world, int positionY, int positionX, string plantType)
{
	this->strength = SOW_STRENGTH;
	this->initiative = PLANTS_INITIATIVE;
	this->organismName = plantType;
	this->gridPresentation = 't';
	this->positionY = positionY;
	this->positionX = positionX;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void SowThistle::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void SowThistle::addOrganism(class World* world, int positionY, int positionX)
{
	SowThistle* tmp = new SowThistle(world, positionY, positionX);
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

void SowThistle::action()
{
	int sowing, direction;
	bool spaceForNewPlant;
	bool sowNewPlant = false;
	int newPlantPositionY = positionY, newPlantPositionX = positionX;

	for (int i = 0; i < 3; i++)				//sow thistle performs 3 attempts at spreading in each turn
	{
		sowing = rand() % 100;
		if (sowing < SOW_PROPABILITY)		//plant will sow to free neighboring cell
		{

			spaceForNewPlant = spaceForNewAnimal(world, positionY, positionX);
			if (spaceForNewPlant)
			{
				while (world->grid[newPlantPositionY][newPlantPositionX] != ' ')
				{
					newPlantPositionY = positionY;
					newPlantPositionX = positionX;

					do
					{
						direction = rand() % 4 + 1;
					} while (!newPositionInsideGrid(world, direction, positionY, positionX));

					newPosition(direction, &newPlantPositionY, &newPlantPositionX);
				}

				cout << "New " << organismName << " at at (" << newPlantPositionX + 1 << "," << newPlantPositionY + 1 << ") was sowned." << endl;
				addOrganism(world, newPlantPositionY, newPlantPositionX);
				sowNewPlant = true;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
	if (!sowNewPlant)
	{
		cout << organismName << " didn't sow new plant." << endl;
	}

	draw();
}