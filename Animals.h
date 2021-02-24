#pragma once
#include "Organism.h"

class Animal :public Organism
{
public:
	virtual void action();
	virtual void collision(int typeOfCollision, int newPositionY, int newPositionX);
};

class Wolf :public Animal
{
public:
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Wolf(class World* world, int positionY, int positionX, string animalName = "Wolf");
};

class Sheep :public Animal
{
public:
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Sheep(class World* world, int positionY, int positionX, string animalName = "Sheep");
};

class Fox :public Animal
{
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Fox(class World* world, int positionY, int positionX, string animalName = "Fox");
};

class Turtle :public Animal
{
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Turtle(class World* world, int positionY, int positionX, string animalName = "Turtle");
};

class Antelope :public Animal
{
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Antelope(class World* world, int positionY, int positionX, string animalName = "Antelope");
};

class Human :public Animal
{
private:
	bool activatedSpecialAbility;
	int turnActivated;
	int turnDisactivated;
public:
	virtual void action();
	virtual void draw();
	virtual void addOrganism(class World* world, int positionY, int positionX);
	Human(class World* world, int positionY, int positionX, string humanName = "Human");
};