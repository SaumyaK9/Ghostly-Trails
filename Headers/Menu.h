#ifndef MENU
#define MENU

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"
#include <chrono>

class Menu
{
	const static int width{ 1620 };
	const static int height{ 1100 };
	const std::array<std::string, 4> credits = { "Game created by: " ,"Saumya Karmalkar" ,"as a Minor Project" ,"See more at: " };
	int status = 1; //1 - active, schow buttons, 2 - active, show credits, 0 - inactive
	std::array<bool, 3> menuChoices{ false,false,false }; //(active = 1, inactive = 0, exit game = false)
	bool demandedCredits = false;

	sf::Sprite backgroundSprite;
	std::array<std::unique_ptr<Button>, 5> buttons;

	sf::Text menuText;
	sf::Text creditsText;

	static constexpr std::chrono::milliseconds holdTime{ 200 };
	std::chrono::time_point<std::chrono::steady_clock> timeStamp;

public:

	Menu();

	// Method that draws all menu components
	void displayMenu(sf::RenderWindow& win);

	// Method checks state of all buttons and sets menu state accordingly
	std::array<bool, 3> menuLogic(sf::RenderWindow& win);

	// Method displays menu's sub page, it has credits text displayed and "back" button 
	void displayCredits(sf::RenderWindow& win);

	// changes a boolean value "demandedCredits" based on given param
	void checkForDemand(bool creditsNeeded);

	// When this function is called, it measured 200ms, then ends
	void waitFunction();

	// Method sets up all needed parameters for SFML text.
	void setUpText();

	// Method configures all buttons of the menu, first 4 sets as acitve, fifth as inactive
	void initializeButtons();

	// Returns a status of the menu
	inline bool getStatus()
	{
		return status;
	}
};


#endif
