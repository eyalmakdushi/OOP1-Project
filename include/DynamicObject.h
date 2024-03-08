#pragma once
#include "BaseObject.h"

class Wall;
class Cookie;
class Door;
class Gift;
class Key;

class DynamicObject : public BaseObject
{
public:
	virtual ~DynamicObject() = default;
	virtual void move(sf::Time) = 0;

	virtual void handleCollisionWithStatic(const Wall&) = 0;
	virtual void handleCollisionWithStatic(Cookie& cookie) = 0;
	virtual void handleCollisionWithStatic(Door& door) = 0;
	virtual void handleCollisionWithStatic(Gift& gift) = 0;
	virtual void handleCollisionWithStatic(Key& key) = 0;
	virtual void moveFromObstacle(const sf::Vector2f newPos);

	void resetPosition();

protected:
	DynamicObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);

	void setDirection(const sf::Vector2f direction);
	sf::Vector2f getDirection() const;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	void moveLeft();
	void moveRight();

	sf::Vector2f getStartPosition() const;
	void setStartPosition(const sf::Vector2f startPos);
	void moveFromObstacle();
	void setLastPosition(sf::Vector2f);

private:
	sf::Vector2f m_direction;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_lastPosition;
};
