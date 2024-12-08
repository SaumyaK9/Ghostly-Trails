#include "TextBox.h"

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext)
{
	setUpText(text, _text, 150);
	//place text
	text.setPosition(_x + _w / 2, _y + _h / 8);

	setUpText(subtext, _subtext, 55);
	//place subtext
	subtext.setPosition(_x + _w / 2, _y + _h / 2);

	setUpFrame(_x, _y, _w, _h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 2, _y + _h - 150, sf::Color(113, 114, 168), "Back"));
	buttons[0]->setActive();
}

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel)
{
	setUpText(text, _text, 150);
	//place text
	text.setPosition(_x + _w / 2, _y + _h / 8);

	setUpText(subtext, _subtext, 55);
	//place subtext
	subtext.setPosition(_x + _w / 2, _y + _h / 2);

	setUpFrame(_x, _y, _w, _h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 2, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel));
	buttons[0]->setActive();
}

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel1, std::string buttonLabel2)
{
	setUpText(text, _text, 150);
	//place text
	text.setPosition(_x + _w / 2, _y + _h / 8);

	setUpText(subtext, _subtext, 55);
	//place subtext
	subtext.setPosition(_x + _w / 2, _y + _h / 2);

	setUpFrame(_x, _y, _w, _h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 4, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel1));
	buttons.emplace_back(std::make_unique<Button>(_x - 150 + 3 * _w / 4, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel2));
	buttons[0]->setActive();
	buttons[1]->setActive();
}

void TextBox::setUpText(sf::Text& text, std::string s, float textSize)
{
	text.setFont(FileManager::get_ttl(FileManager::FONT_TTL));
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color(100, 200, 200));
	text.setStyle(sf::Text::Bold);
	text.setString(s);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
}

void TextBox::setUpFrame(int _x, int _y, int _w, int _h)
{
	frame.setPosition(_x, _y);
	frame.setOutlineColor(sf::Color(100, 200, 200));
	frame.setOutlineThickness(15.f);
	frame.setSize(sf::Vector2f(_w, _h));
	frame.setFillColor(sf::Color::Transparent);
}

void TextBox::turnFrame(bool on_off)
{
	useFrame = on_off;
}

void TextBox::fillFrame(bool on_off)
{
	fullFrame = true;
}

void TextBox::displayTextBox(sf::RenderWindow& win)
{
	if (useFrame)
	{
		if (fullFrame && frame.getFillColor() == sf::Color::Transparent)
			frame.setFillColor(sf::Color(60, 90, 90));
		win.draw(frame);
	}
	win.draw(text);
	win.draw(subtext);

	for (int q{ 0 }; q < buttons.size(); q++)
		buttons[q]->displayButton(win);
}

std::pair<bool, int>  TextBox::waitForButton(sf::RenderWindow& win)
{
	int index = -1;

	if (buttons[0]->checkIfButtonPressed(win))
	{
		index = 0;
		isActive = false;
	}
	else if (buttons.size() > 1 && buttons[1]->checkIfButtonPressed(win))
	{
		index = 1;
		isActive = false;
	}
	return std::make_pair(isActive, index);
}
