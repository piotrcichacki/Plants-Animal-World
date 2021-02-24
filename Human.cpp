#include "Animals.h"
#include <iostream>
#include <conio.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define HUMAN_STRENGTH 5
#define HUMAN_INITIATIVE 4

Human::Human(class World* world, int positionY, int positionX, string humanName)
{
	this->activatedSpecialAbility = false;
	this->turnActivated = 0;
	this->turnDisactivated = 0;
	this->strength = HUMAN_STRENGTH;
	this->initiative = HUMAN_INITIATIVE;
	this->organismName = humanName;
	this->gridPresentation = 'H';
	this->positionX = positionX;
	this->positionY = positionY;
	this->world = world;
	this->indexAge = world->numberOfOrganism;
	world->grid[positionY][positionX] = gridPresentation;
	world->numberOfOrganism++;
}

void Human::draw()
{
	world->grid[positionY][positionX] = gridPresentation;
}

void Human::action()
{
	int direction, newPositionY = positionY, newPositionX = positionX, index, typeOfCollision;
	int key;
	int decision;

	if (!activatedSpecialAbility && turnDisactivated == 0)
	{
		cout << "If you want to activate purification for human press 'a'" << endl;
	}
	else if (!activatedSpecialAbility && turnDisactivated > 0)
	{
		turnDisactivated--;
		cout << "You cannot activate special ability for the next " << turnDisactivated << " turns" << endl;
	}
	if (activatedSpecialAbility)
	{
		turnActivated--;
		cout << "Human has activated purification for the next " << turnActivated << " turns." << endl;
	}

	if (activatedSpecialAbility)
	{
		for (int i = 1; i <= 4; i++)	//go through 4 neighboring cells (up, left, right, down)
		{
			newPositionY = positionY;
			newPositionX = positionX;
			index = 0;

			if (newPositionInsideGrid(world, i, positionY, positionX))
			{
				newPosition(i, &newPositionY, &newPositionX);
				if (world->grid[newPositionY][newPositionX] != ' ') //checks whether in neighboring cell is animal or plant
				{
					index = world->findOrganism(newPositionY, newPositionX);
					if (world->organisms[index]->getGridPresentation() <= 'Z' && world->organisms[index]->getGridPresentation() >= 'A')
						cout << organismName << " killed " << world->organisms[index]->getOrganismName() << endl;
					else
						cout << organismName << " ate " << world->organisms[index]->getOrganismName() << endl;

					world->grid[newPositionY][newPositionX] = ' ';
					world->deleteOrganism(index);
				}
			}
		}
	}

	newPositionY = positionY;
	newPositionX = positionX;

	cout << "Choose direction of movement for human" << endl << endl;
	//world->drawWorld();

	do
	{
		do
		{
			key = _getch();
			if (key == 'a')
			{
				cout << "Now human destroys all animals and plants that are adjacent to his position" << endl;
				activatedSpecialAbility = true;
				turnActivated = 5;
			}
		} while (key != 224);

		if (key == 224)						//direction of movement corresponds to the arrow keys pressed by player
		{
			switch (key = _getch())
			{
			case KEY_UP:
				direction = UP;
				break;
			case KEY_LEFT:
				direction = LEFT;
				break;
			case KEY_DOWN:
				direction = DOWN;
				break;
			case KEY_RIGHT:
				direction = RIGHT;
				break;
			default:

				break;
			}
		}
	} while (!newPositionInsideGrid(world, direction, positionY, positionX));
	newPosition(direction, &newPositionY, &newPositionX);


	if (world->grid[newPositionY][newPositionX] == ' ')
		typeOfCollision = EMPTY_CELL;
	else if (world->grid[newPositionY][newPositionX] == 'T')
		typeOfCollision = MEET_TURTLE;
	else if (world->grid[newPositionY][newPositionX] == 'A')
		typeOfCollision = MEET_ANTELOPE;
	else if (world->grid[newPositionY][newPositionX] == 's' || world->grid[newPositionY][newPositionX] == 't' || world->grid[newPositionY][newPositionX] == 'g' || world->grid[newPositionY][newPositionX] == 'b' || world->grid[newPositionY][newPositionX] == 'h')
		typeOfCollision = MEET_PLANT;
	else
		typeOfCollision = FIGHT;

	collision(typeOfCollision, newPositionY, newPositionX);

	if (activatedSpecialAbility)
	{
		for (int i = 1; i <= 4; i++)	//go through 4 neighboring cells (up, left, right, down)
		{
			newPositionY = positionY;
			newPositionX = positionX;
			index = 0;

			if (newPositionInsideGrid(world, i, positionY, positionX))
			{
				newPosition(i, &newPositionY, &newPositionX);
				if (world->grid[newPositionY][newPositionX] != ' ') //checks whether in neighboring cell is animal or plant
				{
					index = world->findOrganism(newPositionY, newPositionX);
					if (world->organisms[index]->getGridPresentation() <= 'Z' && world->organisms[index]->getGridPresentation() >= 'A')
						cout << organismName << " killed " << world->organisms[index]->getOrganismName() << endl;
					else
						cout << organismName << " ate " << world->organisms[index]->getOrganismName() << endl;
					world->grid[newPositionY][newPositionX] = ' ';
					world->deleteOrganism(index);
				}
			}
		}
	}

	if (turnActivated == 0 && activatedSpecialAbility == true)						//end of special ability
	{
		activatedSpecialAbility = false;
		turnDisactivated = 5;
	}
}

//there won't be another human so empty function
void Human::addOrganism(class World* world, int positionY, int positionX)
{

}