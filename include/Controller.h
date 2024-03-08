#pragma once
//---- include section ----
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <string>

#include "Screen.h"

using std::ifstream;

//---- const section ----
const int WIN_PIC = 19;
const int LOSE_PIC = 20;
const int WIN_SOUND = 0;
const int LOSE_SOUND = 1;

//---- class section ----
class Controller
{
public:
	Controller() = default;
	Controller(const Controller&) = delete;
	void operator = (const Controller&) = delete;

	void startGame();
	void startInitializiation();

private:
	void prepareLevel();
	void repeatLevel();
	void readTxtFile();

	void handleTimeLimit(const char charFromFile);
	void addObjectsToGame();

	//window funcs:
	void showLosingWindow();
	void showWinningWindow();
	void waitForEvents(sf::RenderWindow& window) const;

	int m_numOfRows, m_numOfCols = 0;
	
	Screen m_screen;

	float m_timeLimit = NO_TIME_LIMIT;
	std::ifstream m_file = std::ifstream("Board.txt");
	std::vector <std::string> m_levelLines;
};