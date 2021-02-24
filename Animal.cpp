#include "Animals.h"
#include <iostream>
#include <stdlib.h>   

using namespace std;

//default for animals
void Animal::action()
{
	int direction = 0, typeOfCollision = 0;
	int newPositionY = positionY, newPositionX = positionX;

	do
	{
		direction = rand() % 4 + 1;
	} while (!newPositionInsideGrid(world, direction, positionY, positionX));

	newPosition(direction, &newPositionY, &newPositionX);

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


//default for animals
void Animal::collision(int typeOfCollision, int newPositionY, int newPositionX)
{
	int direction = 0;
	int newAnimalPositionY = positionY, newAnimalPositionX = positionX;
	int index = 0;
	int escapeFromFight = 0, freeCellPositionY, freeCellPositionX;
	bool freeNeighbourhoodCell = false;


	switch (typeOfCollision)
	{
	case EMPTY_CELL:
		cout << organismName << " moved from (" << positionX + 1 << "," << positionY + 1 << ") to (" << newPositionX + 1 << "," << newPositionY + 1 << ")." << endl;
		world->grid[positionY][positionX] = ' ';
		positionY = newPositionY;
		positionX = newPositionX;
		draw();
		break;

	case THE_SAME_SPACIES:
		cout << organismName << " met the same species at (" << newPositionX + 1 << "," << newPositionY + 1 << ")." << endl;
		if (spaceForNewAnimal(world, positionY, positionX))
		{
			while (world->grid[newAnimalPositionY][newAnimalPositionX] != ' ')
			{
				newAnimalPositionY = positionY;
				newAnimalPositionX = positionX;

				do
				{
					direction = rand() % 4 + 1;
				} while (!newPositionInsideGrid(world, direction, positionY, positionX));

				newPosition(direction, &newAnimalPositionY, &newAnimalPositionX);
			}
			cout << "New animal at (" << newAnimalPositionX + 1 << "," << newAnimalPositionY + 1 << ") was created." << endl;
			addOrganism(world, newAnimalPositionY, newAnimalPositionX);
		}
		draw();
		break;

	case FIGHT:
		index = world->findOrganism(newPositionY, newPositionX);

		cout << organismName << " met " << world->organisms[index]->getOrganismName() << ". There will be a fight!" << endl;
		if (strength >= world->organisms[index]->getStrength())
		{
			cout << organismName << " won the fight! " << world->organisms[index]->getOrganismName() << " is dead!" << endl;
			world->deleteOrganism(index);
			world->grid[positionY][positionX] = ' ';
			positionY = newPositionY;
			positionX = newPositionX;
			draw();
		}
		else
		{
			cout << world->organisms[index]->getOrganismName() << " won the fight! " << organismName << " is dead!" << endl;
			world->grid[positionY][positionX] = ' ';
			world->deleteOrganism(indexAge);
		}
		break;

		//Turtle eflects attacks of animal with strength less than 5. Attacker will return to the previous cell.
	case MEET_TURTLE:
		if (strength < 5)
		{
			cout << "Turtle reflected attack of " << organismName << endl;
			draw();
		}
		else
		{
			collision(FIGHT, newPositionY, newPositionX);
		}
		break;

		//Antelope has 50% chance to escape from fight.
	case MEET_ANTELOPE:
		escapeFromFight = rand() % 2;
		if (escapeFromFight == 0)					//antelope does not escape from fight	
		{
			collision(FIGHT, newPositionY, newPositionX);
		}
		else
		{
			freeNeighbourhoodCell = spaceForNewAnimal(world, newPositionY, newPositionX);
			if (!freeNeighbourhoodCell)				//there is no free neighboring cell for antelope to escape
			{
				escapeFromFight = 0;
				collision(FIGHT, newPositionY, newPositionX);
			}
			else									//antelope escapes to free neighboring cell
			{
				freeCellPositionY = newPositionY;
				freeCellPositionX = newPositionX;

				while (world->grid[freeCellPositionY][freeCellPositionX] != ' ')
				{
					freeCellPositionY = newPositionY;
					freeCellPositionX = newPositionX;

					do
					{
						direction = rand() % 4 + 1;
					} while (!newPositionInsideGrid(world, direction, newPositionY, newPositionX));

					newPosition(direction, &freeCellPositionY, &freeCellPositionX);
				}
				index = world->findOrganism(newPositionY, newPositionX);			//find index of antelope on this position where animal want to move

				world->organisms[index]->setPositionY(freeCellPositionY);			//change position of antelope
				world->organisms[index]->setPositionX(freeCellPositionX);
				world->grid[freeCellPositionY][freeCellPositionX] = 'A';
				world->grid[newPositionY][newPositionX] = ' ';
				cout << world->organisms[index]->getOrganismName() << " escaped from fight and moved to (" << freeCellPositionX + 1 << "," << freeCellPositionY + 1 << ")." << endl;

				collision(EMPTY_CELL, newPositionY, newPositionX);
			}
		}
		break;

	case MEET_PLANT:
		index = world->findOrganism(newPositionY, newPositionX);
		if (world->grid[newPositionY][newPositionX] == 't' || world->grid[newPositionY][newPositionX] == 's' || world->grid[newPositionY][newPositionX] == 'g')
		{
			cout << organismName << " ate " << world->organisms[index]->getOrganismName() << " and moved on its position (" << newPositionX + 1 << "," << newPositionY + 1 << ").";

			if (world->grid[newPositionY][newPositionX] == 'g')			//Strength of the animal which ate guarana is permanently increased by 3
			{
				strength += 3;
				cout << " His strength permanently increased by 3.";
			}
			cout << endl;

			world->deleteOrganism(index);
			world->grid[positionY][positionX] = ' ';
			positionY = newPositionY;
			positionX = newPositionX;
			draw();
		}
		else if (world->grid[newPositionY][newPositionX] == 'b' || world->grid[newPositionY][newPositionX] == 'h')
		{
			cout << organismName << " ate " << world->organisms[index]->getOrganismName() << " and died." << endl;

			world->grid[newPositionY][newPositionX] = ' ';
			world->deleteOrganism(index);
			world->grid[positionY][positionX] = ' ';
			world->deleteOrganism(indexAge);
		}
		break;
	}
}

