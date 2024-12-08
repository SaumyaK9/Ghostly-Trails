#include "InfoPanel.h"

InfoPanel::InfoPanel(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h)
{
	setUpText(tLev, 50);
	setUpText(tHp, 350);
	setUpText(tComp, 750);
}

void InfoPanel::setNewInfo(int level, int hp, double percent, double percent_needed)
{
	s_levels = std::to_string(level);
	s_hp = std::to_string(hp);

	s_completion = std::to_string(percent);
	s_completion = s_completion.substr(0, 4);

	std::string tmp_s_percent = std::to_string(percent_needed);
	tmp_s_percent = tmp_s_percent.substr(0, 4);

	s_completion += "%/" + tmp_s_percent + "%";
}

void InfoPanel::drawInfo(sf::RenderWindow& win)
{
	tLev.setString(prefix_levels + s_levels);
	tHp.setString(prefix_hp + s_hp);
	tComp.setString(prefix_completion + s_completion);

	win.draw(tLev);
	win.draw(tHp);
	win.draw(tComp);
}

void InfoPanel::setUpText(sf::Text& t, int offset_x)
{
	t.setFont(FileManager::get_ttl(FileManager::FONT_TTL));
	t.setCharacterSize(60);
	t.setFillColor(sf::Color(127, 224, 227));
	t.setStyle(sf::Text::Bold);

	//place text
	sf::FloatRect textRect = t.getLocalBounds();
	t.setOrigin(textRect.width / 2, textRect.height / 2);
	t.setPosition(x + offset_x, y + height / 6);
}
