#ifndef DESTROYER
#define DESTROYER

#include "Enemy.h"

class DestroyerEnemy : public Enemy
{
public:

	DestroyerEnemy(float _x, float _y, int sp);
	// Check if any collision occurred, moves entity by a vector/// </summary>
	void move(Map& map) override;

	// Changes entity velcity any time a collison with a tile occured (swaps velocity values)
	bool changeDirection(int param) override;

	// Functions check of whih block(tile) chearacter has bounced. 
	std::pair<int, int> checkBlockInFront(Map& m, std::pair<int, int> vel);

};
#endif
