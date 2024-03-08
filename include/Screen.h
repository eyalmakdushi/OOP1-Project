//---- include section ----
#pragma once
#include "Resources.h"
#include "Board.h"
#include "Clock.h"
#include "Pacman.h"
#include "Demon.h"

const int INFORMATION_BAR_HEIGHT = 100;
const int OUT_OF_COOKIES = 1;
const int FINISH = 0;
const int TIME_OUT = 2;
const int GAME_OVER = 3;

const int FREEZE_SOUND = 8;
const int HOORAY_SOUND = 11;
const int TIME_OUT_SOUND = 12;

const float FREEZING_TIMER = 5;

//---- class section ----
class Screen
{
public:
	Screen();
	Screen(const Screen&) = delete;
	void operator = (const Screen&) = delete;

	//----------------- initialization funcs: -----------------
	void openGameWindow();
	void initializeDataMembers();
	void addTimeLimit(const float timeLimit);

	//get funcs:
	float getTimeLimit() const;
	Pacman& getPacmanPtr();

	//calling board funcs
	void initializePacman();
	void prepareForLevel(const int rows, const int cols);
	void addObjectsToGame(const int row, const int col, const char object);

	//----------------- object update funcs: -----------------
	void freezeDemons();
	void resetDemonsPosition();
	
	//----------------- level managing funcs: -----------------
	int runLevel();
	int timeOut();
	int gameOver();
	int wonLevel();
	void closeGameWindow(); //to close the window of the game after finishing it (losing or winning)
	
private:
	sf::Vector2f calculatePosition(const int row, const int col) const;

	//----------------- window funcs: -----------------
	void manageWindow();
	void draw();
	sf::Text prepareInformation();
	void pollEvent();

	//----------------- board funcs: -----------------
	void manageBoard();
	void moveFigures();
	void handleCollisions();

	//----------------- data members: -----------------
	Board m_board;
	std::vector <Demon> m_demonsVec;
	std::unique_ptr <Pacman> m_pacmanPtr;

	//general members: 
	int m_levelNumber = 1;
	bool m_firstKeyPressed = false;

	//window related members: 
	sf::RenderWindow m_window;
	sf::Font m_font = Resources::instance().getFont();

	//time related members: 
	Clock m_levelClock;
	Clock m_timeLimitClock;
	Clock m_moveClock;
	Clock m_frozenDemonsClock;
	float m_timeLimit, m_remainingTime, m_frozen, m_remainingFrozen = NO_TIME_LIMIT;
};