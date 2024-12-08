#ifndef INFO_P
#define INFO_P

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "FileManager.h"

class InfoPanel
{
	std::string prefix_levels{ "Level: " };
	std::string prefix_hp{ "Lives left: " };
	std::string prefix_completion{ "Level completion: " };

	std::string s_levels;
	std::string s_hp;
	std::string s_completion;

	sf::Text tLev;
	sf::Text tHp;
	sf::Text tComp;

	int x;
	int y;
	int width;
	int height;

	// Method sets up all needed parameters for SFML text.
	void setUpText(sf::Text& t, int offset_x);

public:

	InfoPanel(int _x, int _y, int _w, int _h);

	// actualizes information displayed on the panel	
	void setNewInfo(int level, int hp, double percent, double percent_needed);

	// Method draws all elements of info panel
	void drawInfo(sf::RenderWindow& win);

};

#endif
