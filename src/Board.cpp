#include "Board.h"
#include "Resources.h"
#include "Cookie.h"
#include "Wall.h"
#include "Door.h"
#include "Key.h"
#include "TimeGift.h"
#include "LifeGift.h"
#include "FreezeGift.h"
#include "SuperGift.h"
#include "Screen.h"

Board::Board(Screen* screen)
	: m_rows(0), m_cols(0), m_scaleRatio(0.f)
{
	m_screenPtr = screen;
}

void Board::prepareBoardForLevel(const int rows, const int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_scaleRatio = calculateScaleRatio();
	clearMat();
}

void Board::clearMat()
{
	for (int row = 0; row < m_staticMat.size(); ++row)
		m_staticMat[row].clear(); //delete contents of previous vector

	m_staticMat.clear(); //delete the old 2D vector

	for (int row = 0; row < m_rows; ++row)
	{
		m_staticMat.push_back(std::vector <std::unique_ptr <StaticObject>>());

		for (int col = 0; col < m_cols; ++col)
			m_staticMat[row].push_back(std::unique_ptr <StaticObject>());
	}
}

float Board::calculateScaleRatio() const
{
	float rowScale = float(SCREEN_EDGE_SIZE) / float(IMAGE_EDGE_SIZE) / m_rows;
	float colScale = float(SCREEN_EDGE_SIZE) / float(IMAGE_EDGE_SIZE) / m_cols;

	return std::min(rowScale, colScale);
}

float Board::getScaleRatio() const
{
	return m_scaleRatio;
}

int Board::getRows() const
{
	return m_rows;
}

int Board::getCols() const
{
	return m_cols;
}

void Board::addObjectToBoard(const int row, const int col, const char object, const sf::Vector2f position)
{
	switch (object)
	{
	case (COOKIE):
		m_staticMat[row][col] = std::make_unique <Cookie>(Resources::instance().getTexture(cookie), m_scaleRatio, position);
		break;

	case (DOOR):
		m_staticMat[row][col] = std::make_unique <Door>(Resources::instance().getTexture(door), m_scaleRatio, position);
		break;

	case (GIFT):
		createGift(row, col, position);
		break;

	case(KEY):
		m_staticMat[row][col] = std::make_unique <Key>(Resources::instance().getTexture(key), m_scaleRatio, position);
		break;

	case(WALL):
		m_staticMat[row][col] = std::make_unique <Wall>(Resources::instance().getTexture(wall), m_scaleRatio, position);
	}
}

void Board::createGift(const int row, const int col, const sf::Vector2f position)
{
	if (m_screenPtr->getTimeLimit() == NO_TIME_LIMIT)
	{
		int giftType = rand() % 3;

		if (giftType == 0)
			m_staticMat[row][col] = std::make_unique <LifeGift>(Resources::instance().getTexture(life),
																m_scaleRatio, position, *m_screenPtr);

		else if (giftType == 1)
			m_staticMat[row][col] = std::make_unique <FreezeGift>(Resources::instance().getTexture(freeze),
																  m_scaleRatio, position, *m_screenPtr);

		else if (giftType == 2)
			m_staticMat[row][col] = std::make_unique <SuperGift>(Resources::instance().getTexture(super),
																 m_scaleRatio, position, *m_screenPtr);
	}

	else
	{
		int giftType = rand() % 4;

		if (giftType == 0)
			m_staticMat[row][col] = std::make_unique <LifeGift>(Resources::instance().getTexture(life),
																m_scaleRatio, position, *m_screenPtr);

		else if (giftType == 1)
			m_staticMat[row][col] = std::make_unique <FreezeGift>(Resources::instance().getTexture(freeze),
																	m_scaleRatio, position, *m_screenPtr);

		else if (giftType == 2)
			m_staticMat[row][col] = std::make_unique <SuperGift>(Resources::instance().getTexture(super),
																 m_scaleRatio, position, *m_screenPtr);

		else
			m_staticMat[row][col] = std::make_unique <TimeGift>(Resources::instance().getTexture(timeGift),
																m_scaleRatio, position, *m_screenPtr);
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (int row = 0; row < m_staticMat.size(); ++row)
	{
		for (int col = 0; col < m_staticMat[row].size(); ++col)
			if (m_staticMat[row][col] != nullptr)
				m_staticMat[row][col]->draw(window);
	}
}

void Board::handleCollisions(DynamicObject& figure)
{
	//collision with static
	for (auto row = size_t(0); row < m_staticMat.size(); ++row)
		for (auto col = size_t(0); col < m_staticMat[row].size(); ++col)
			if (m_staticMat[row][col] != nullptr)
			{
				if (m_staticMat[row][col]->checkCollision(figure))
					m_staticMat[row][col]->handleCollision(figure);
			}
}

void Board::removeDisposedObjects()
{
	for (auto row = size_t(0); row < m_staticMat.size(); ++row)
		for (auto col = size_t(0); col < m_staticMat[row].size(); ++col)
			std::erase_if(m_staticMat[row], [](auto& staticObj)
				{
					if (staticObj != nullptr)
						return staticObj -> isDisposed();

					else
						return false; //to avoid Warning C4715
					//`4'::<lambda_1>::operator() < std::unique_ptr<StaticObject, std::default_delete<StaticObject> > > ':
					//not all control paths return a value
				});
}
