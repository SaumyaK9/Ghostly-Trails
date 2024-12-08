#ifndef KEYBOARD
#define KEYBOARD

#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"

class KeyboardImput
{
	std::shared_ptr<Player> player;

public:

	// Default constructor
	KeyboardImput() {};

	// Constructor which takes pointer to Player, allows to pass kayboard imput to be passed futher 
	KeyboardImput(std::shared_ptr<Player> p);

	// Sets a pointer to a player object 
	void setPlayer(std::shared_ptr<Player> p);

	// Method check selected buttons states and process events
	void checkKeyboardImput(bool& activatePause);
};
#endif
