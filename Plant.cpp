#include "Plants.h"
#include <iostream>
#include <stdlib.h>   


using namespace std;

//default for plants
void Plant::action()
{
	int sowing, direction;
	bool spaceForNewPlant;
	int newPlantPositionY = positionY, newPlantPositionX = positionX;

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

			cout << "New " << organismName << " at (" << newPlantPositionX + 1 << "," << newPlantPositionY + 1 << ") was sowned." << endl;
			addOrganism(world, newPlantPositionY, newPlantPositionX);
		}
		else
		{
			cout << organismName << " didn't sow new plant." << endl;
		}
	}
	else
	{
		cout << organismName << " didn't sow new plant." << endl;
	}
	draw();
}

//plants don't move so they will never cause collision, that's why this function is empty
void Plant::collision(int typeOfCollision, int newPositionY, int newPositionX)
{

}
