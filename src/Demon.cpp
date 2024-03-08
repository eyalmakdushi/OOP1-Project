#include "Demon.h"

Demon::Demon(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, const Pacman& pacman)
	: DynamicObject(texture, scaleRatio, position), m_speedPerSecond(200 * scaleRatio), m_movingTime(NO_TIME_LIMIT),
	  m_pacmanPositionPtr (pacman.getPacmanPosition())
{
	m_moveClock.restart();

	int randColor = rand() % 5;
	m_randMove = rand() % 2;

	switch (randColor)
	{
	case RED:
		changeSprite().setColor(sf::Color::Red);
		break;

	case BLUE:
		changeSprite().setColor(sf::Color::Blue);
		break;

	case GREEN:
		changeSprite().setColor(sf::Color::Green);
		break;

	case YELLOW:
		changeSprite().setColor(sf::Color::Yellow);
		break;

	default:
		break;
	}

	m_originalColor = getSprite().getColor();
}

void Demon::frozenSprite()
{
	changeSprite().setColor(sf::Color::Cyan);
}

void Demon::normalSprite()
{
	changeSprite().setColor(m_originalColor);
}

// --------------------- move funcs: ---------------------
void Demon::move(const sf::Time deltaTime)
{
	if (m_remainingMovingTime < -1)
	{
		m_moveClock.restart();
		m_movingTime = m_remainingMovingTime = ((float)rand()) / (float)RAND_MAX;

		m_randMove = rand() % 5;

		if (m_randMove != CHASE)
			moveRandom();

		else
			chasePacman();
	}

	if (m_remainingMovingTime > -1 && m_randMove == CHASE)
	{
		chasePacman();
		m_remainingMovingTime = m_movingTime - m_moveClock.getSeconds();
	}

	else
		m_remainingMovingTime = m_movingTime - m_moveClock.getSeconds();

	setLastPosition(getSprite().getPosition());
	changeSprite().move(getDirection() * m_speedPerSecond * deltaTime.asSeconds());
}

void Demon::chasePacman()
{
	auto xDistance = std::abs(m_pacmanPositionPtr->x - getSprite().getPosition().x);
	auto yDistance = std::abs(m_pacmanPositionPtr->y - getSprite().getPosition().y);

	if (xDistance > yDistance)
	{
		if (m_pacmanPositionPtr->x < getSprite().getPosition().x)
			moveLeft();

		else if (m_pacmanPositionPtr->x > getSprite().getPosition().x)
			moveRight();
	}

	else 
	{
		if (m_pacmanPositionPtr->y < getSprite().getPosition().y)
			moveUp();

		else if (m_pacmanPositionPtr->y > getSprite().getPosition().y)
			moveDown();
	}
}

void Demon::moveRandom()
{
	int randMove = rand() % 5;

	switch (randMove)
	{
	case LEFT:
		moveLeft();
		break;

	case UP:
		moveUp();
		break;

	case RIGHT:
		moveRight();
		break;

	case DOWN:
		moveDown();
	}
}

void Demon::moveUp()
{
	setDirection(sf::Vector2f(0, -1));
}

void Demon::moveDown()
{
	setDirection(sf::Vector2f(0, 1));
}

// --------------------- handleCollision funcs: ---------------------
void Demon::handleCollision(DynamicObject& other)
{
	other.handleCollision(*this);
}

void Demon::handleCollisionWithStatic(const Wall&)
{
	moveFromObstacle();
}

void Demon::handleCollisionWithStatic(Cookie&)
{}

void Demon::handleCollisionWithStatic(Door&)
{
	moveFromObstacle();
}

void Demon::handleCollisionWithStatic(Gift&)
{}

void Demon::handleCollisionWithStatic(Key&)
{}