#include "World.h"
#include "Animals.h"
#include "Plants.h"
#include <iostream>
#include <stdlib.h>   
#include <time.h> 
#include <conio.h>
#include <fstream>

using namespace std;

#define WOLF 1
#define SHEEP 2
#define FOX 3
#define TURTLE 4
#define ANTELOPE 5
#define GRASS 6
#define SOW_THISTLE 7
#define GUARANA 8
#define BELLADONNA 9
#define SOSNOWSKYS_HOGWEED 10
#define HUMAN 11

void printInitialGrid(class World* world);

void addOrganismToWorld(class World* world, int type, int positionY, int positionX, string name);

void saveToFile(class World* world);

void loadFromFile(class World* world);

int main()
{
	char input;
	srand(time(NULL));
	World world;

	/*
	addOrganismToWorld(&world, WOLF, 2, 1, "Wolf 1");
	addOrganismToWorld(&world, WOLF, 8, 4, "Wolf 2");
	addOrganismToWorld(&world, WOLF, 6, 9, "Wolf 3");

	addOrganismToWorld(&world, SHEEP, 8, 8, "Sheep 1");
	addOrganismToWorld(&world, SHEEP, 1, 10, "Sheep 2");
	addOrganismToWorld(&world, SHEEP, 9, 5, "Sheep 3");

	addOrganismToWorld(&world, FOX, 2, 2, "Fox 1");
	addOrganismToWorld(&world, FOX, 8, 6, "Fox 2");

	addOrganismToWorld(&world, TURTLE, 0, 3, "Turtle 1");
	addOrganismToWorld(&world, TURTLE, 7, 11, "Turtle 2");

	addOrganismToWorld(&world, ANTELOPE, 0, 8, "Antelope 1");
	addOrganismToWorld(&world, ANTELOPE, 10, 10, "Antelope 2");

	addOrganismToWorld(&world, SOSNOWSKYS_HOGWEED, 5, 5, "---");
	addOrganismToWorld(&world, SOSNOWSKYS_HOGWEED, 9, 9, "---");

	addOrganismToWorld(&world, BELLADONNA, 10, 3, "---");
	addOrganismToWorld(&world, BELLADONNA, 1, 7, "---");

	addOrganismToWorld(&world, GRASS, 4, 2, "---");
	addOrganismToWorld(&world, GRASS, 7, 6, "---");

	addOrganismToWorld(&world, SOW_THISTLE, 11, 11, "---");
	addOrganismToWorld(&world, SOW_THISTLE, 4, 10, "---");

	addOrganismToWorld(&world, GUARANA, 0, 1, "---");
	addOrganismToWorld(&world, GUARANA, 5, 7, "---");

	addOrganismToWorld(&world, HUMAN, 0, 0, "Piotr");
	*/


	loadFromFile(&world);

	printInitialGrid(&world);


	input = getc(stdin);
	while (input != 'q')
	{
		world.makeTurn();
		input = _getch();
		if (input == 's')
		{
			saveToFile(&world);
			cout << "State of the world was saved to the file" << endl;
			input = _getch();
		}
	}

	return 0;
}

void printInitialGrid(class World* world)
{
	cout << "Initial grid:" << endl << endl;
	world->drawWorld();
	cout << endl << endl;
	cout << "Symbols of specific organisms on the grid:" << endl;
	cout << "W - Wolf" << endl;
	cout << "S - Sheep" << endl;
	cout << "F - Fox" << endl;
	cout << "T - Turtle" << endl;
	cout << "A - Antelope" << endl;
	cout << "s - Grass" << endl;
	cout << "t - Sow thistle" << endl;
	cout << "g - Guarana" << endl;
	cout << "b - Belladona" << endl;
	cout << "h - Sosnowsky's hogweed" << endl;
}

void addOrganismToWorld(class World* world, int type, int positionY, int positionX, string name)
{
	class Organism* tmp = NULL;
	switch (type)
	{
	case WOLF:
		tmp = new Wolf(world, positionY, positionX, name);
		break;
	case SHEEP:
		tmp = new Sheep(world, positionY, positionX, name);
		break;
	case FOX:
		tmp = new Fox(world, positionY, positionX, name);
		break;
	case TURTLE:
		tmp = new Turtle(world, positionY, positionX, name);
		break;
	case ANTELOPE:
		tmp = new Antelope(world, positionY, positionX, name);
		break;
	case GRASS:
		tmp = new Grass(world, positionY, positionX);
		break;
	case SOW_THISTLE:
		tmp = new SowThistle(world, positionY, positionX);
		break;
	case GUARANA:
		tmp = new Guarana(world, positionY, positionX);
		break;
	case BELLADONNA:
		tmp = new Belladonna(world, positionY, positionX);
		break;
	case SOSNOWSKYS_HOGWEED:
		tmp = new Hogweed(world, positionY, positionX);
		break;
	case HUMAN:
		tmp = new Human(world, positionY, positionX, name);
		break;
	}
	world->organisms[world->numberOfOrganism - 1] = tmp;
	tmp = NULL;
	delete[] tmp;
}

void saveToFile(class World* world)
{
	ofstream myfile;
	myfile.open("output.txt");
	//myfile << "Index  -  Organism name  -  PositionY  -  PositionX  -  Strength  -  Initiative" << endl;
	myfile << world->numberOfOrganism << endl;
	for (int i = 0; i < world->numberOfOrganism; i++)
	{
		myfile << world->organisms[i]->getGridPresentation() << " " << world->organisms[i]->getOrganismName() << " " << world->organisms[i]->getPositionY() << " " << world->organisms[i]->getPositionX() << " " << world->organisms[i]->getStrength() << " " << world->organisms[i]->getInitiative() << endl;
	}
	myfile.close();
}

void loadFromFile(class World* world)
{
	int numberOfOrganisms = 0;
	char gridPresentation;
	string organismName;
	int positionY, positionX, strength, initiative;
	string line;

	ifstream myfile("output.txt");
	if (myfile.is_open())
	{
		myfile >> numberOfOrganisms;
		for (int i = 0; i < numberOfOrganisms; i++)
		{
			myfile >> gridPresentation;
			myfile >> organismName;
			myfile >> positionY;
			myfile >> positionX;
			myfile >> strength;
			myfile >> initiative;
			getline(myfile, line);
			switch (gridPresentation)
			{
			case 'W':
				addOrganismToWorld(world, WOLF, positionY, positionX, organismName);
				break;
			case 'S':
				addOrganismToWorld(world, SHEEP, positionY, positionX, organismName);
				break;
			case 'F':
				addOrganismToWorld(world, FOX, positionY, positionX, organismName);
				break;
			case 'T':
				addOrganismToWorld(world, TURTLE, positionY, positionX, organismName);
				break;
			case 'A':
				addOrganismToWorld(world, ANTELOPE, positionY, positionX, organismName);
				break;
			case 's':
				addOrganismToWorld(world, GRASS, positionY, positionX, organismName);
				break;
			case 't':
				addOrganismToWorld(world, SOW_THISTLE, positionY, positionX, organismName);
				break;
			case 'g':
				addOrganismToWorld(world, GUARANA, positionY, positionX, organismName);
				break;
			case 'b':
				addOrganismToWorld(world, BELLADONNA, positionY, positionX, organismName);
				break;
			case 'h':
				addOrganismToWorld(world, SOSNOWSKYS_HOGWEED, positionY, positionX, organismName);
				break;
			case 'H':
				addOrganismToWorld(world, HUMAN, positionY, positionX, organismName);
				break;
			default:
				break;
			}
			world->organisms[world->numberOfOrganism - 1]->setStrength(strength);
			world->organisms[world->numberOfOrganism - 1]->setInitiative(initiative);
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}
