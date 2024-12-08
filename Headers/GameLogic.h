#ifndef LOGIC
#define LOGIC

#include "Enemy.h"
#include "DefaultEnemy.h"
#include "DestroyerEnemy.h"
#include "HunterEnemy.h"

#include "Map.h"
#include "Player.h"

#include "KeyboardImput.h"
#include "GWindow.h"
#include "FileManager.h"

#include <memory>
#include <thread>
#include <vector>


class GameLogic
{
	bool gameOver = false;
	bool isMenuActive = true;
	bool isPauseActive = false;
	bool isDefeatBoxActive = false;
	bool isGameCompleted = false;

	int hitPoints; //+1 after finished level, -1 if any game over condition met
	int nextLevelIndex = 2;
	int currentLevelIndex = 1;
	static const int maxLevels = 20;

	std::vector<std::string> levels;
	std::vector<int> levelInfo;
	std::vector<int> nextLevelInfo;

	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Enemy>> nextLevelEnemies;

	KeyboardImput kI;
	GWindow winG;

	std::thread nextLevelLoader;

public:

	// Constructor, invokes game loop
	GameLogic() { start(); };

	// Method initialises game menu, then invokes set up methods and run method
	void start();

	// Basically a game loop, invokes event handling methods and drawing methods every frame
	void run();

	// Method then set up basic game components 
	void initializeGame(bool doLoadGame);

	// Sets up new enemies, resets mapa and player position
	void setUpNextLevel();

	// Checks area covered in Wall tiles and compares it to percentage needed to completion
	bool checkLevelCompletion();

	// Gets level information from the string and converts it to integers
	void getLevelInformation(int index);

	// Asks for level information and initialize all enemies
	void prepareNextLevel(int lvlIndex);

	// Handles operations related to entities movement and tile filling
	void calculateLogic();

	// Check if conditons to decrement players hit points have been met
	// Checks if enemies touched the tail and activates tail crumbling
	bool checkLivesLossConditions();

	// Takes care of all events possible in game loop (game logic and interface)
	void handleEvents();

	// Calculates all events related to game logic specifically
	void handleGameConditions();

	// Method inveked every time player looses a hp. Resets its position to starting point
	void deathProc();

	// Draws all entities active on the window
	void drawEntities();

	// Draws all panels ("static objects") in the window
	void drawPanels();

	// Saves via FileManager current game state
	void saveGame();

	// Loads information from file about last saved game state
	void loadGame();

	// Fills all empty tiles touching enemy entities with mask value
	void drop(int XY);

	// Invokes drop method for every enemy and tells Map object to fill unmasked tiles
	void conquer(std::vector<int> positions);

	~GameLogic();
};

#endif //LOGIC
