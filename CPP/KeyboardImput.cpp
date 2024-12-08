#include "KeyboardImput.h"

KeyboardImput::KeyboardImput(std::shared_ptr<Player> p) : player(p) {}

void KeyboardImput::setPlayer(std::shared_ptr<Player> p) { player = p; }

void KeyboardImput::checkKeyboardImput(bool& activatePause)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		activatePause = true;
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			player->planNextTurn(0, -1, 270);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			player->planNextTurn(0, 1, 90);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->planNextTurn(-1, 0, 180);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->planNextTurn(1, 0, 0);
	}
}
