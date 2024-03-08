#pragma once
#include <SFML/Graphics.hpp>

class DynamicObject;
const int IMAGE_EDGE_SIZE = 50;
const int SCREEN_EDGE_SIZE = 800;

class BaseObject
{
public:
	virtual ~BaseObject() = default;

	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getGlobalBounds() const;
	virtual bool checkCollision(DynamicObject& other) const;
	virtual void handleCollision(DynamicObject& other) = 0;

protected:
	BaseObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
	sf::Sprite getSprite() const;
	sf::Sprite& changeSprite();
	const sf::Vector2f* const getSpritePosition() const; //for demons to know pacman's position

private:
	sf::Sprite m_sprite;
};