#include "World.h"
#include <iostream>
#include <conio.h>
using namespace std;

//constructor creates grid of specific sizes and array of pointers to organisms
World::World(int dimensionY, int dimensionX)
{
	this->numberOfOrganism = 0;
	this->numberOfTurn = 1;
	this->dimensionX = dimensionX;
	this->dimensionY = dimensionY;
	grid = new char* [dimensionY];
	for (int i = 0; i < dimensionY; i++)
	{
		grid[i] = new char[dimensionX];
		grid[i] = new char[dimensionX];
		for (int j = 0; j < dimensionX; j++)
		{
			grid[i][j] = ' ';
		}
	}
	organisms = new Organism * [dimensionY * dimensionX];
	for (int i = 0; i < dimensionY * dimensionX; i++)
	{
		organisms[i] = NULL;
	}
}

int World::getDimensionX() {
	return dimensionX;
}

int World::getDimensionY() {
	return dimensionY;
}

//drawWorld print on screen grid
void World::drawWorld()
{
	for (int i = 0; i < dimensionY; i++)
	{
		for (int j = 0; j < 2 * dimensionX + 1; j++)
		{
			cout << (char)196;
		}
		cout << endl;
		for (int j = 0; j < dimensionX; j++)
		{
			cout << '|' << grid[i][j];
		}
		cout << '|' << endl;
	}
	for (int j = 0; j < 2 * dimensionX + 1; j++)
	{
		cout << (char)196;
	}
	cout << endl;
}

//makeTurn carry out one turn
void World::makeTurn()
{
	sortOrganisms();

	system("CLS");
	cout << "Piotr Cichacki\t s180277" << endl << endl;
	cout << "Turn number: " << numberOfTurn << endl << endl;
	numberOfTurn++;

	numberOfOrganismInTurn = numberOfOrganism;						//new created organisms do not perform action during current turn

	for (int i = 0; i < numberOfOrganismInTurn; i++)
	{
		cout << i + 1 << ". ";
		organisms[i]->action();
	}
	cout << endl;
	drawWorld();
	cout << endl << "Press enter to go to the next turn" << endl;
	cout << "Q - quit game" << endl;
	cout << "S - save state of world to file" << endl << endl;
}

//sortOrganisms function sort array of organism according to their initiative (organisms with bigger initiatives moves first)
void World::sortOrganisms()
{
	class Organism* maksInitiative;
	int indexMaks;

	for (int i = 0; i < numberOfOrganism - 1; i++)
	{
		maksInitiative = organisms[i];
		indexMaks = i;

		for (int j = i + 1; j < numberOfOrganism; j++)
		{
			if (organisms[j]->getInitiative() > maksInitiative->getInitiative())
			{
				maksInitiative = organisms[j];
				indexMaks = j;
			}
		}
		for (int j = indexMaks; j > i; j--)
		{
			organisms[j] = organisms[j - 1];
			organisms[j]->setIndexAge(j);
		}
		organisms[i] = maksInitiative;
		organisms[i]->setIndexAge(i);
	}
}

//deleteOrganism delete organism defeated in collision
void World::deleteOrganism(int index)
{
	organisms[index] = NULL;
	for (int i = index; i < numberOfOrganism - 1; i++)
	{
		organisms[i] = organisms[i + 1];
		organisms[i]->decrementIndex();
	}
	organisms[numberOfOrganism - 1] = NULL;
	numberOfOrganism--;
	numberOfOrganismInTurn--;
}

//findOrganism find organism in array with specific position and returns its index in array
int World::findOrganism(int positionY, int positionX)
{
	for (int i = 0; i < numberOfOrganism; i++)
	{
		if (positionY == organisms[i]->getPositionY() && positionX == organisms[i]->getPositionX())
		{
			return i;
		}
	}

}


