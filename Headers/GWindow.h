#ifndef G_WINDOW
#define G_WINDOW

#include <memory>
#include <SFML/Graphics.hpp>
#include "InfoPanel.h"
#include "Menu.h"
#include "TextBox.h"
#include "FileManager.h"

class GWindow
{
	sf::RenderWindow window;

	std::unique_ptr<Menu> menu;
	std::unique_ptr<InfoPanel> iP;
	std::unique_ptr<TextBox> tB;

	// Method sets basic window parameters, fixed number of frames per second is equeal to 60
	void config();

	// Methos sets a icon of an app, takes needed png form file
	void setGameIcon();

public:
	bool pasuseBoxInitialized = false;
	bool demandCredits = false;

	const static int width{ 1620 };
	const static int height{ 1100 };

	GWindow();

	// Method initializes a Menu object
	void setMenu();

	// Releases memory taken by memory instance
	void deleteMenu();

	// Methot invokes a menus metod to draw, check buttons statement
	std::array<bool, 3> displayMenu();

	// Returns a reference to window variable
	sf::RenderWindow& getWindow();

	// Sets up a text box configured as: defeat information box
	void setDefeatBox();

	// Sets up a text box configured as: pause box
	void setPauseBox();

	// Sets up a text box configured as: victory information box
	void setVictoryBox();

	// displays active text box, invokes drawing method of the box 
	void displayTextBox();

	// Asks for active text box's buttons state
	std::pair<bool, int> getTextBoxResponse();

	// Sets up info panel
	void setInfoPanel(int _x, int _y, int _w, int _h);

	// Displays info panel and actualises its data
	void displayInfoPanel(int level, int hp, double percent, double percent_needed);
};

#endif
