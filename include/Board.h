#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"

class Screen;

//---- const section ----
const char COOKIE = '*';
const char DOOR = 'D';
const char KEY = '%';
const char WALL = '#';
const char PACMAN = 'a';
const char DEMON = '&';
const char EMPTY = ' ';
const char GIFT = '$';

enum picureIndices
{
	pacman,
	demon,
	cookie,
	door,
	key,
	wall,
	freeze,
	timeGift,
	life,
	super,
	superPacman
};

class Board
{
public:
	Board(Screen* screen);
	Board(const Board& otherBoard) = delete;
	Board& operator = (const Board& otherBoard) = delete;

	//initialization funcs:
	void prepareBoardForLevel(const int rows, const int cols);
	void clearMat();
	float calculateScaleRatio() const;
	void addObjectToBoard(const int row, const int col, const char object, const sf::Vector2f position);

	//window funcs:
	void draw (sf::RenderWindow& window);
	void handleCollisions(DynamicObject& figure);
	void removeDisposedObjects();

	//get funcs:
	float getScaleRatio() const;
	int getRows() const;
	int getCols() const;

private:
	void createGift(const int row, const int col, const sf::Vector2f position);
	
	std::vector <std::vector <std::unique_ptr <StaticObject>>> m_staticMat;

	Screen* m_screenPtr;
	int m_rows, m_cols = 0;
	float m_scaleRatio = 0.f;
};