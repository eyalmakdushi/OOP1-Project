//---- include section ----
#pragma once
#include "DynamicObject.h"
#include "Wall.h"
#include "Cookie.h"
#include "Door.h"
#include "Gift.h"
#include "Key.h"
#include "Pacman.h"

//---- const section ----
const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

const int RED = 0;
const int BLUE = 1;
const int GREEN = 2;
const int YELLOW = 3;

const int CHASE = 0;

//---- class section ----
class Demon : public DynamicObject
{
public:
	Demon(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, const Pacman& pacman);
	void move(sf::Time) override;

	void frozenSprite();
	void normalSprite();

	void handleCollision(DynamicObject& other) override;
	void handleCollisionWithStatic(const Wall&);
	void handleCollisionWithStatic(Cookie&) override;
	void handleCollisionWithStatic(Door&) override;
	void handleCollisionWithStatic(Gift&)  override;
	void handleCollisionWithStatic(Key&) override;

private:
	float m_speedPerSecond;
	const sf::Vector2f* m_pacmanPositionPtr;
	sf::Color m_originalColor;
	Clock m_moveClock;
	int m_randMove = 0;
	float m_movingTime, m_remainingMovingTime = NO_TIME_LIMIT;

	void chasePacman();
	void moveRandom();
	void moveUp();
	void moveDown();
};