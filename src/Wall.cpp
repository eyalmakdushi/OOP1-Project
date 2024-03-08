#include "Wall.h"

Wall::Wall(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: StaticObject(texture, scaleRatio, position)
{}

bool Wall::checkCollision(DynamicObject& other) const
{
	return getSprite().getGlobalBounds().intersects(other.getGlobalBounds());
}

void Wall::handleCollision(DynamicObject& other)
{
	other.handleCollisionWithStatic(*this);
}