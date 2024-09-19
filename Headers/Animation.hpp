#ifndef ANIM
#define ANIM

#include <SFML/Graphics.hpp>
#include <chrono>


class Animation
{
	std::chrono::milliseconds holdTime{ 100 };
	int frames{ 8 };

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	int currentFrame{ 0 };

public:

	Animation();
	
	// Switches a animation frame (sets sprite rectTxt on texture)
	void applyToSprite(sf::Sprite& s);
	
	// Updates the index of a frame if enough time has passed
	bool update();

	// Starts measuring time
	void startMeasureTime(int howLong_ms);

	// Checks if time determined in startMeasureTime method has passed
	bool checkIfTimePassed();
};


#endif
