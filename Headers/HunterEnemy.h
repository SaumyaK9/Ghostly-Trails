#ifndef HUNT
#define HUNT

#include <memory>
#include "Enemy.h"
#include "Player.h"

class HunterEnemy : public Enemy
{
	std::shared_ptr<Player> victim;
	std::pair<int, int> spawnPoint;

public:

	HunterEnemy(float _x, float _y, int sp, std::shared_ptr<Player> p);

	// Method unused in this context, always returns false
	bool changeDirection(int param) override;

	// Check if any collision occurred, moves entity based on current position of player character (to shorten the distance between entities)
	void move(Map& map) override;

	// In case player character is not in reach, entity next move is to get closer to its initial spawning point
	void calmDown();
};


#endif
