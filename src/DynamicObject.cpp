#include "DynamicObject.h"

DynamicObject::DynamicObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: BaseObject(texture, scaleRatio, position), m_startPosition(position)
{}

void DynamicObject::setDirection(const sf::Vector2f direction)
{
	m_direction = direction;
}

sf::Vector2f DynamicObject::getDirection() const
{
	return m_direction;
}

void DynamicObject::moveFromObstacle(const sf::Vector2f newPos)
{
	changeSprite().setPosition(newPos);
}

void DynamicObject::resetPosition()
{
	//if the figure doesn't face right, set its direction to right
	if (getSprite().getScale().x < 0)
		changeSprite().scale(-1, 1);

	changeSprite().setRotation(0.f);

	changeSprite().setPosition(m_startPosition);
}

void DynamicObject::moveLeft()
{
	if (getSprite().getScale().x > 0)
		changeSprite().scale(-1, 1);

	m_direction = sf::Vector2f(-1, 0);
	changeSprite().setRotation(0.f);
}

void DynamicObject::moveRight()
{
	if (getSprite().getScale().x < 0)
		changeSprite().scale(-1, 1);

	changeSprite().setRotation(0.f);
	m_direction = sf::Vector2f(1, 0);
}

sf::Vector2f DynamicObject::getStartPosition() const
{
	return m_startPosition;
}

void DynamicObject::setStartPosition(const sf::Vector2f startPos)
{
	m_startPosition = startPos;
}

void DynamicObject::moveFromObstacle()
{
	changeSprite().setPosition(m_lastPosition);
}

void DynamicObject::setLastPosition(const sf::Vector2f lastPos)
{
	m_lastPosition = lastPos;
}