#pragma once
#include "Organism.h"

//default dimensions of grid
#define DIMENSION_Y 12
#define DIMENSION_X 12

//class which will manage the gameplay and life cycle of organisms
class World
{
private:
	int dimensionY, dimensionX;
	int numberOfTurn;
public:
	char** grid;
	class Organism** organisms;
	int numberOfOrganism;
	int numberOfOrganismInTurn;
	int getDimensionX();
	int getDimensionY();

	World(int dimensionY = DIMENSION_Y, int dimensionX = DIMENSION_X);
	void drawWorld();
	void makeTurn();
	void sortOrganisms();
	void deleteOrganism(int index);
	int findOrganism(int positionY, int positionX);
};
