#include "Door.h"

Door::Door(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: StaticObject(texture, scaleRatio, position)
{}

bool Door::checkCollision(DynamicObject& other) const
{
	return getSprite().getGlobalBounds().intersects(other.getGlobalBounds());
}

void Door::handleCollision(DynamicObject& other)
{
	other.handleCollisionWithStatic(*this);
}

void Door::dispose()
{
	Resources::instance().playSound(DOOR_SOUND);
	setDisposed();
}
