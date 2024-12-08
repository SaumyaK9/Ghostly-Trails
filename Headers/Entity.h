#ifndef ENTITY
#define ENTITY

#include <memory>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Map.h"
#include "FileManager.h"

class Entity
{
protected:
	std::pair<float, float> velocity;
	int speed;

	sf::Sprite body;

	std::unique_ptr<Animation> animation;
	Entity() = delete;

	// Gets a desirable texture from FileManager resources 
	void loadTextures(int type);

public:

	constexpr static int ENTITY_RADIUS = 15;
	Entity(int s);

	virtual void move(Map& map) = 0;

	// Draws entity sprite in the window
	void draw(sf::RenderWindow& win);

	// Calculates coordinates of bottom center of the entity (middle of the edge)
	std::pair<int, int> getDside();
	// Calculates coordinates of upper center of the entity (middle of the edge) 
	std::pair<int, int> getUside();
	// Calculates coordinates of left center of the entity (middle of the edge)
	std::pair<int, int> getLside();
	// Calculates coordinates of right center of the entity (middle of the edge)
	std::pair<int, int> getRside();
	// Check if entity has touched given entity 
	bool chcekEntityCollions(Entity& e);
	// Checks if entity touched any Tail tile
	std::pair<bool, int> checkTailCollisons(Map& map);

};
#endif
