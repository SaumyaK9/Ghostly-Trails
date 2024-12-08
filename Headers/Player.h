#ifndef PLAYER
#define PLAYER

#include <set>
#include "Entity.h"

class Player : public Entity
{
private:
	// Structure that is used to hold data needed for change of entity direction
	struct nextMove
	{
		bool inQueue = false;
		std::pair<int, int> nextVelocity = { 0,0 };
		float nextRotation = 0;
	};

	nextMove nM;
	bool conquestPossible = false;
	bool playerEntered = false;

	// Check if player is currently on empty tile or wall tile and matches its state accordingly
	bool checkPlayerState(int state);

	// Checks if player is on any crumbling tile;
	bool checkCrumbleCollison(Map& map);

	// Resets player position to starting position
	void revivePlayer();

	// Method handles all aspect of character movement
	void move(Map& map) override;

	// Method sets up nextMove struture to hold all data needed for change of direction
	void planNextTurn(int x, int y, float degree);

	// Method check collisions with map borders and prevents entity from leaving
	void checkCollisons(sf::Vector2f pos);

	// Changes velocity of the player
	void changeVelocity(float x, float y);

	// Rotates player's sprite by certain degrees
	void rotate(float angle);

	bool getConquestState();

	friend class GameLogic;
	friend class KeyboardImput;

public:

	Player(int s);

	std::pair<int, int> getPositionPx();


	// Method checks what tile type is bellow player sprite
	std::pair<int, int> checkTileBellow(Map& map);
};

#endif
