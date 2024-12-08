#ifndef ENEMY_DEFAULT
#define ENEMY_DEFAULT

#include <random>
#include <iostream>
#include "Entity.h"
class Enemy : public Entity
{
	int type;
protected:

	Enemy(int speed) : Entity(speed) {};

	// Method changes velocity and direction of entity after certain conditions 
	virtual bool changeDirection(int param) = 0;

	// Method check if entity has collided with any tile on map considered as WALL type
	int checkWallCollisons(Map& map);

	// Method uses random number generator to give random number in range
	int getRandomStartingPos(int rangeFrom, int rangeTo);

public:
	// Calculates an index of the tile bellow center of this entity
	int getIndexOfTile();
};

#endif
