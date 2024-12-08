#ifndef BUT
#define BUT

#include <memory>
#include <SFML/Graphics.hpp>
#include "FileManager.h"

// Class represents a button that has a label and background inage, can be pressed using left mouse button
class Button
{
	int x{ 0 };
	int y{ 0 };

	const int width{ 300 };
	const int height{ 150 };
	std::string label{ "BUTTON" };

	bool active = true;
	sf::Color color = sf::Color::White;

	sf::Sprite bodyButton;
	sf::Text buttonText;

public:

	Button(int _x, int _y, sf::Color c, std::string _label);

	// Method draws button elements on the window
	void displayButton(sf::RenderWindow& win);

	// Sets up SFML text parameters 
	void setUpText();

	// Method checks button statement (basing on mouse state and position in relation to window and button)
	bool checkIfButtonPressed(sf::RenderWindow& win);

	// Sets button active (can be pressed)
	inline void setActive()
	{
		active = true;
	}

	// Sets button inactive (can not be pressed)
	inline void setInactive()
	{
		active = false;
	}
};


#endif
