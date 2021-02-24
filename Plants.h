#pragma once
#include "Organism.h"

#define SOW_PROPABILITY 25
#define PLANTS_INITIATIVE 0

class Plant :public Organism
{
public:
	virtual void action();
	virtual void collision(int typeOfCollision, int newPositionY, int newPositionX);
};

class Grass :public Plant
{
public:
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Grass(class World* world, int positionY, int positionX, string plantType = "Grass");
};

class SowThistle :public Plant
{
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	SowThistle(class World* world, int positionY, int positionX, string plantType = "Sow thistle");
};

class Guarana :public Plant
{
public:
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Guarana(class World* world, int positionY, int positionX, string plantType = "Guarana");
};

class Belladonna :public Plant
{
public:
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Belladonna(class World* world, int positionY, int positionX, string plantType = "Belladonna");
};

class Hogweed :public Plant
{
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Hogweed(class World* world, int positionY, int positionX, string plantType = "Sosnowsky's_hogweed");
};
