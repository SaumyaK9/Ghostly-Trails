#ifndef F_MANAGER
#define F_MANAGER
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <regex>
#include <iostream>
#include <memory>
#include <filesystem>

class FileManager
{
private:
	static std::unique_ptr<sf::Texture> player_tx;
	static std::unique_ptr<sf::Texture> blue_enemy_tx;
	static std::unique_ptr<sf::Texture> green_enemy_tx;
	static std::unique_ptr<sf::Texture> background_tx;
	static std::unique_ptr<sf::Texture> wall_tx;
	static std::unique_ptr<sf::Texture> button_tx;
	static std::unique_ptr<sf::Font> font_ttl;
	static int chosedBackground;
	FileManager() {};
public:

	const static int PLAYER_TX = 0;
	const static int BLUE_ENEMY_TX = 1;
	const static int GREEN_ENEMY_TX = 2;
	const static int BACKGROUND_TX = 3;
	const static int WALL_TX = 4;
	const static int BUTTON_TX = 5;
	const static int FONT_TTL = 6;
	// Get reference to choosen texture
	static sf::Texture& get_tx(int type);
	// Get reference to choosen font
	static sf::Font& get_ttl(int type);
	// Reads resources needed for game graphics form files
	static void setUpResources();
	// Releases dymiamicly allocated resources
	static void resetResources();
	// Swaps contents of background_tx variable with difrent image
	static void swapBackgroundImage(int swap);
	// Reads a png/img/bmp file
	static sf::Image openImage(std::filesystem::path path);
	// Reads a .TTF file
	static void openTTFfile(sf::Font& f, std::filesystem::path path);
	// Reads form file
	static void readFromFile(std::string& contener, std::filesystem::path path);
	// Reads form file
	static void readFromFile(std::vector<std::string>& contener, std::filesystem::path path);
	// Reads specific map config file and invokes validation method, fixes contents if needed
	static void readMapFile(std::array<int, 1620>& a, std::filesystem::path path);
	// Reads specific levels config file and invokes validation method
	static void readLevelsFile(std::vector<std::string>& l, std::filesystem::path path);
	// Method checks if contents of levels configuration file matches the format using regex
	static bool validateLevels(std::vector<std::string>& l);
	// Creates a new file
	static bool createFile(std::filesystem::path path, std::string name, std::string content);
	// Creates a new file
	static bool createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents);
	// Method checks if contents of map configuration file matches the format using regex
	static bool validateMap(std::string mS);
	// Method checks if contents of save file matches the format using regex
	static bool validateSaves(std::vector<std::string> sav);
	// Edits existing file, filles it with new content
	static bool editFile(std::filesystem::path path, std::vector<std::string> contents);
	// Edits existing file, filles it with new content
	static bool editFile(std::filesystem::path path, std::string content);
	// Check if directory or file exists
	static bool checkDir(std::filesystem::path path);
	// Creates directory of a given name under given path
	static bool createDir(std::filesystem::path path, std::string name);
};

#endif 
