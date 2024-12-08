#include "Button.h"

Button::Button(int _x, int _y, sf::Color c, std::string _label)
	: x(_x), y(_y), color(c), label(_label)
{
	bodyButton.setTexture(FileManager::get_tx(FileManager::BUTTON_TX));
	bodyButton.setColor(color);
	bodyButton.setPosition(sf::Vector2f(x, y));

	setUpText();
};

void Button::displayButton(sf::RenderWindow& win)
{
	win.draw(bodyButton);
	win.draw(buttonText);
}

void Button::setUpText()
{
	buttonText.setFont(FileManager::get_ttl(FileManager::FONT_TTL));
	buttonText.setString(label);
	buttonText.setCharacterSize(55);
	buttonText.setFillColor(sf::Color(169, 179, 186));
	buttonText.setStyle(sf::Text::Bold);

	//center text
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.width / 2, textRect.height / 2);
	buttonText.setPosition(sf::Vector2f(x + width / 2, y + (3 * height / 8)));

}

bool Button::checkIfButtonPressed(sf::RenderWindow& win)
{
	if (active && sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
	{
		sf::Vector2i mPos = sf::Mouse::getPosition(win);
		if (mPos.x >= x && mPos.x <= x + width && mPos.y >= y && mPos.y <= y + height)
			return true;
	}
	return false;
}
