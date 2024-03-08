#include "Gift.h"

Gift::Gift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: StaticObject(texture, scaleRatio, position)
{}

void Gift::handleCollision(DynamicObject& other)
{
	other.handleCollisionWithStatic(*this);
}
