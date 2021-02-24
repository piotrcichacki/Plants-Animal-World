#include "Organism.h"
#include <iostream>
#include <stdlib.h> 


//newPositionInsideGrid function checks whether possible new coordinates are inside grid
bool newPositionInsideGrid(class World* world, int direction, int currentPositionY, int currentPositionX)
{
	switch (direction)
	{
	case UP:
		return (currentPositionY - 1 >= 0);
		break;
	case RIGHT:
		return (currentPositionX + 1 < world->getDimensionX());
		break;
	case DOWN:
		return (currentPositionY + 1 < world->getDimensionY());
		break;
	case LEFT:
		return (currentPositionX - 1 >= 0);
		break;
	}
}

//newPositionInsideGridAntelope function checks whether possible new coordinates are inside grid (in movement by two fields)
bool newPositionInsideGrid2(class World* world, int direction, int currentPositionY, int currentPositionX)
{
	switch (direction)
	{
	case UP:
		return (currentPositionY - 2 >= 0);
		break;
	case RIGHT:
		return (currentPositionX + 2 < world->getDimensionX());
		break;
	case DOWN:
		return (currentPositionY + 2 < world->getDimensionY());
		break;
	case LEFT:
		return (currentPositionX - 2 >= 0);
		break;
	}
}

//newPosition function establish new coordinates according to direction of movement
void newPosition(int direction, int* newPositionY, int* newPositionX)
{
	switch (direction)
	{
	case UP:
		(*newPositionY)--;
		break;
	case RIGHT:
		(*newPositionX)++;
		break;
	case DOWN:
		(*newPositionY)++;
		break;
	case LEFT:
		(*newPositionX)--;
		break;
	}
}

//newPosition function establish new coordinates according to direction of movement by two fields
void newPosition2(int direction, int* newPositionY, int* newPositionX)
{
	switch (direction)
	{
	case UP:
		(*newPositionY) -= 2;
		break;
	case RIGHT:
		(*newPositionX) += 2;
		break;
	case DOWN:
		(*newPositionY) += 2;
		break;
	case LEFT:
		(*newPositionX) -= 2;
		break;
	}
}

//spaceForNewAnimal function checks whether it is possibility to create new organism next to organism
//if one of the neighboring cells is empty, then function return true
bool spaceForNewAnimal(class World* world, int positionY, int positionX)
{
	if (positionY > 0 && world->grid[positionY - 1][positionX] == ' ') return true;
	if (positionY < world->getDimensionY() - 1 && world->grid[positionY + 1][positionX] == ' ') return true;
	if (positionX > 0 && world->grid[positionY][positionX - 1] == ' ') return true;
	if (positionX < world->getDimensionX() - 1 && world->grid[positionY][positionX + 1] == ' ') return true;
	return false;
}

//spaceToMove function checks whether there is place to move for fox where is weaker organism than fox
bool spaceToMove(class World* world, int positionY, int positionX, int strength)
{
	int index;
	bool isThereSpace = false;

	if (isThereSpace == false && positionY > 0 && world->grid[positionY - 1][positionX] == ' ')
		isThereSpace = true;
	else if (isThereSpace == false && positionY > 0)
	{
		index = world->findOrganism(positionY - 1, positionX);
		if (strength >= world->organisms[index]->getStrength())
			isThereSpace = true;
	}
	if (isThereSpace == false && positionY < world->getDimensionY() - 1 && world->grid[positionY + 1][positionX] == ' ')
		isThereSpace = true;
	else if (isThereSpace == false && positionY < world->getDimensionY() - 1)
	{
		index = world->findOrganism(positionY + 1, positionX);
		if (strength >= world->organisms[index]->getStrength())
			isThereSpace = true;
	}
	if (isThereSpace == false && positionX > 0 && world->grid[positionY][positionX - 1] == ' ')
		isThereSpace = true;
	else if (isThereSpace == false && positionX > 0)
	{
		index = world->findOrganism(positionY, positionX - 1);
		if (strength >= world->organisms[index]->getStrength())
			isThereSpace = true;
	}
	if (isThereSpace == false && positionX < world->getDimensionX() - 1 && world->grid[positionY][positionX + 1] == ' ')
		isThereSpace = true;
	else if (isThereSpace == false && positionX < world->getDimensionX() - 1)
	{
		index = world->findOrganism(positionY, positionX + 1);
		if (strength >= world->organisms[index]->getStrength())
			isThereSpace = true;
	}
	return isThereSpace;
}
