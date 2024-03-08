#include "Key.h"

Key::Key(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: StaticObject(texture, scaleRatio, position)
{}

void Key::handleCollision(DynamicObject& other)
{
	other.handleCollisionWithStatic(*this);
}