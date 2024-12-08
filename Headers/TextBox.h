#ifndef TEXT_BOX
#define TEXT_BOX

#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"

class TextBox
{
	sf::Text text;
	sf::Text subtext;

	std::vector<std::unique_ptr<Button>> buttons;

	bool useFrame{ true };
	bool fullFrame{ false };
	sf::RectangleShape frame;

	bool isActive = true;

	// Method sets up all needed parameters for SFML text.
	void setUpText(sf::Text& text, std::string s, float textSize);

	// Method sets up all needed parameters for SFML drawable rectangle.
	void setUpFrame(int _x, int _y, int _w, int _h);

public:

	// Constructor for default text box
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext);

	// Alternative constructor, allows for change of text on the button
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel);

	// Alternative constructor, creates a text box with extra button
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel1, std::string buttonLabel2);

	// Method turns on and off visibility of rectangular frame displayed around the box
	void turnFrame(bool on_off);

	// Method turns on and off visibility background color of the box, if left invisible box is transparent
	void fillFrame(bool on_off);

	// Method draws the box together with buttons and text in the window
	void displayTextBox(sf::RenderWindow& win);

	// Method check if any of active buttons have been presed
	std::pair<bool, int> waitForButton(sf::RenderWindow& win);
};


#endif
