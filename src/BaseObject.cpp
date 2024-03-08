#include "BaseObject.h"
#include "DynamicObject.h"

BaseObject::BaseObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: m_sprite(sf::Sprite(texture))
{
	m_sprite.setScale(scaleRatio, scaleRatio); //to keep proportions and fit into the screen
	m_sprite.setPosition(position);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize() / 2u));
}

sf::Sprite BaseObject::getSprite() const
{
	return m_sprite;
}

sf::Sprite& BaseObject::changeSprite()
{
	return m_sprite;
}

void BaseObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::FloatRect BaseObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

bool BaseObject::checkCollision(DynamicObject& other) const
{
	return other.getGlobalBounds().contains(m_sprite.getPosition());
}

const sf::Vector2f* const BaseObject::getSpritePosition() const
{
	return &m_sprite.getPosition();
}