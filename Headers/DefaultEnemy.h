#ifndef GUARD
#define GUARD

#include "Enemy.h"

class DefaultEnemy : public Enemy
{
public:

	DefaultEnemy(float _x, float _y, int sp);

	// Entity moves by vector given in velocity variable, bouces of any walls
	void move(Map& map) override;

	// Changes entity velcity any time a collison with a tile occured (swaps velocity values)
	bool changeDirection(int param) override;
};

#endif
