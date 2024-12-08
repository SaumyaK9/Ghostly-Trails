#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <array>
#include <ranges>
#include <memory>
#include "FileManager.h"
#include "Animation.h"

class Map
{
	sf::Sprite backgroundSprite;

	std::unique_ptr<Animation> crumbleCounter;
	bool areTilesCrumbling = false;

	std::array<int, 1620> mapping;

	// Loads and sets background image
	void createBackground();

public:
	const static int MAP_WIDTH = 54; //in blocks
	const static int MAP_HEIGHT = 30;//in blocks
	const static int MAP_WIDTH_PIXELS = 1620; //in blocks
	const static int MAP_HEIGHT_PIXELS = 900;//in blocks

	const static int TILE_SIZE = 30; //in px

	const static int WALL_TILE = 1;
	const static int TAIL_TILE = 2;
	const static int EMPTY_TILE = 0;
	const static int OCCUPIED_TILE = -1;

	const std::array<int, 4> CRUMBLING_TILE = { 3,4,5,6 };

	// Method draws all visible tiles
	void draw(sf::RenderWindow& win) const;

	Map();

	int getTileState(int index);

	// Removes tail tiles from the map and replaces them with empty ones 
	void clearTail();

	// Fills empty tiles (state = 0) with wall tiles ( state = 1 )
	void fillEmptySpace();

	// Changes state of refered tile
	void changeTileState(int index, int newState);

	// Calculates how many percent of the total tiles Wall tiles are covering
	double getProggres();

	// Resets map tiles, sets them acordingly to the file content
	void resetMap();

	// Check if given tile is a tile on the edge of the map
	bool isTileInOuterRing(int index);

	// Method starts chain reaction of transforming tail tiles to crumble tiles
	void startCrumbling(int index);

	// Method escalates crumbling effect on other tiles and updates status on tiles that are already crumbling
	void updateCrumbling();

};

#endif
