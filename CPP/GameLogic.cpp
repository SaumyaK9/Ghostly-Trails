#include "GameLogic.h"

void GameLogic::start()
{
	FileManager::setUpResources();

	while (isMenuActive)
	{
		winG.setMenu();

		std::array<bool, 3> menuChoices = winG.displayMenu();
		isMenuActive = menuChoices[2];

		winG.deleteMenu();

		gameOver = false;
		isPauseActive = false;
		isDefeatBoxActive = false;
		nextLevelIndex = 2;
		currentLevelIndex = 1;

		if (menuChoices[0])
		{
			initializeGame(menuChoices[1]);
			run();
		}
	}
}

void GameLogic::initializeGame(bool doLoadGame)
{
	player = std::make_shared<Player>(6);
	map = std::make_unique<Map>();
	hitPoints = 3;

	kI.setPlayer(player);

	std::thread readThread(FileManager::readLevelsFile, std::ref(levels), "D:/code/projects/Territory Wars/resources/gameSettings/levels.txt");

	if (doLoadGame)
		loadGame();

	readThread.join();

	prepareNextLevel(currentLevelIndex);
	setUpNextLevel();

	if (currentLevelIndex < 20)
		nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this, nextLevelIndex);

	winG.setInfoPanel(0, 900, winG.width, winG.height - 900);
}

void GameLogic::run()
{
	while (!gameOver && winG.getWindow().isOpen())
	{
		sf::Event event;
		while (winG.getWindow().pollEvent(event))
			if (event.type == sf::Event::Closed)
			{
				saveGame();
				winG.getWindow().close();
			}

		///////////////////////////////////////////////////////////////////

		handleEvents();

		///////////////////////////////////////////////////////////////////
		winG.getWindow().clear();
		{
			drawPanels();
			drawEntities();
		}
		winG.getWindow().display();
	}
}

void GameLogic::drawPanels()
{
	map->draw(winG.getWindow());
	winG.displayInfoPanel(currentLevelIndex, hitPoints, map->getProggres(), levelInfo[1]);

	if (isPauseActive || isDefeatBoxActive || isGameCompleted)
		winG.displayTextBox();
}

void GameLogic::drawEntities()
{
	player->draw(winG.getWindow());

	for (int q = 0; q < enemies.size(); q++)
		enemies[q]->draw(winG.getWindow());
}

void GameLogic::handleEvents()
{
	//check for ESC or P keys to be pressed (activates pause)
	kI.checkKeyboardImput(isPauseActive);
	if (isPauseActive && winG.pasuseBoxInitialized == false)
	{
		winG.setPauseBox();
		winG.pasuseBoxInitialized = true;
	}

	//(If none of text boxes are active proced with game logic
	if (!isDefeatBoxActive && !isPauseActive && !isGameCompleted)
	{
		handleGameConditions();
		calculateLogic();
	}

	if ((isDefeatBoxActive || isGameCompleted) && !winG.getTextBoxResponse().first)
	{
		isDefeatBoxActive = false;	isGameCompleted = false; gameOver = true;
		currentLevelIndex = 1;	nextLevelIndex = 2;	hitPoints = 3;
		saveGame();

		if (nextLevelLoader.joinable())
			nextLevelLoader.join();
		nextLevelEnemies.clear();

		winG.demandCredits = true;
	}

	if (isPauseActive)
	{
		std::pair response = winG.getTextBoxResponse();
		if (!response.first)
		{
			if (response.second == 1)
			{
				gameOver = true;
				if (nextLevelLoader.joinable())
					nextLevelLoader.join();
				nextLevelEnemies.clear();

				saveGame();
			}
			winG.pasuseBoxInitialized = false;
			isPauseActive = false;
		}
	}
}

void GameLogic::handleGameConditions()
{
	map->updateCrumbling();

	if (checkLivesLossConditions())
		deathProc();

	if (hitPoints <= 0)
	{
		winG.setDefeatBox();
		isDefeatBoxActive = true;
	}
	else if (checkLevelCompletion())
	{
		++currentLevelIndex;
		++nextLevelIndex;
		if (hitPoints <= 4)
			++hitPoints;

		if (currentLevelIndex <= maxLevels)
		{
			nextLevelLoader.join();
			setUpNextLevel();
			nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this, nextLevelIndex);
		}
		else
		{
			isGameCompleted = true;
			winG.setVictoryBox();
		}
	}
}

void GameLogic::prepareNextLevel(int lvlIndex)
{
	getLevelInformation(lvlIndex);

	for (int q = 0; q < nextLevelInfo[2]; q++)
		nextLevelEnemies.push_back(std::make_shared<DefaultEnemy>(500 + q * 30, 500, 3));
	for (int q = 0; q < nextLevelInfo[3]; q++)
		nextLevelEnemies.push_back(std::make_shared<DestroyerEnemy>(0, 0, 2));
	for (int q = 0; q < nextLevelInfo[4]; q++)
		nextLevelEnemies.push_back(std::make_shared<HunterEnemy>(0, 0, 2, player));
	for (int q = 0; q < nextLevelInfo[5]; q++);
	//TO DO
	for (int q = 0; q < nextLevelInfo[6]; q++);
	//TO DO
}

void GameLogic::setUpNextLevel()
{
	levelInfo = nextLevelInfo;
	player->revivePlayer();
	map->resetMap();

	enemies.clear();
	enemies = nextLevelEnemies;
	nextLevelEnemies.clear();
}

void GameLogic::getLevelInformation(int index)
{
	nextLevelInfo.clear();
	std::string tmpNum;
	for (auto c : levels[index])
	{
		if (c != ';')
			tmpNum.push_back(c);
		else
		{
			nextLevelInfo.push_back(std::stoi(tmpNum));
			tmpNum = "";
		}
	}
}

bool GameLogic::checkLevelCompletion()
{
	if (map->getProggres() >= levelInfo[1])
		return true;
	return false;
}

void GameLogic::calculateLogic()
{
	player->move(*map);

	std::vector<std::thread> threads;

	if (player->getConquestState())
	{
		std::vector<int> t;
		for (int q = 0; q < enemies.size(); q++)
			t.push_back(enemies[q]->getIndexOfTile());
		conquer(t);
	}

	for (int q = 0; q < enemies.size(); q++)
		threads.emplace_back(&Enemy::move, enemies[q].get(), std::ref(*map));
	for (auto& t : threads)
		t.join();
}

bool GameLogic::checkLivesLossConditions()
{
	if (player->checkTailCollisons(*map).first)
		return true;
	if (player->checkCrumbleCollison(*map))
		return true;

	for (int q = 0; q < enemies.size(); q++)
	{
		std::pair infEn = enemies[q]->checkTailCollisons(*map);
		if (infEn.first)
			map->startCrumbling(infEn.second);

		if (enemies[q]->chcekEntityCollions(*player))
			return true;
	}

	return false;
}

void GameLogic::deathProc()
{
	--hitPoints;
	player->revivePlayer();
	map->clearTail();
}

void GameLogic::saveGame()
{
	if (!FileManager::checkDir("D:/code/projects/Territory Wars/resources/Saves"))
		FileManager::createDir("D:/code/projects/Territory Wars/resources", "Saves");

	if (!FileManager::createFile("D:/code/projects/Territory Wars/resources/Saves", "gameSave.txt", std::vector<std::string>{std::to_string(currentLevelIndex), std::to_string(hitPoints)}))
		FileManager::editFile("D:/code/projects/Territory Wars/resources/Saves/gameSave.txt", std::vector<std::string>{std::to_string(currentLevelIndex), std::to_string(hitPoints)});
}

void GameLogic::loadGame()
{
	if (FileManager::checkDir("D:/code/projects/Territory Wars/resources/Saves/gameSave.txt"))
	{
		std::vector<std::string> sLvl{};
		FileManager::readFromFile(sLvl, "D:/code/projects/Territory Wars/resources/Saves/gameSave.txt");

		if (FileManager::validateSaves(sLvl))
		{
			currentLevelIndex = std::stoi(sLvl[0]);
			nextLevelIndex = 1 + currentLevelIndex;
			hitPoints = std::stoi(sLvl[1]);
		}
	}
}

void GameLogic::drop(int XY)
{
	if (map->getTileState(XY) == 0) map->changeTileState(XY, -1);
	if (map->getTileState(XY - Map::MAP_WIDTH) == 0) drop(XY - Map::MAP_WIDTH);
	if (map->getTileState(XY + Map::MAP_WIDTH) == 0) drop(XY + Map::MAP_WIDTH);
	if (map->getTileState(XY - 1) == 0) drop(XY - 1);
	if (map->getTileState(XY + 1) == 0) drop(XY + 1);
}

void GameLogic::conquer(std::vector<int> positions)
{
	for (auto a : positions)
		drop(a);

	map->fillEmptySpace();

	player->conquestPossible = false;
}

GameLogic::~GameLogic()
{
	FileManager::resetResources();

	if (nextLevelLoader.joinable())
		nextLevelLoader.join();
}
