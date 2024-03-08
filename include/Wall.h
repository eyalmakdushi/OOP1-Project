#pragma once
#include "StaticObject.h"

//---- class section ----
class Wall : public StaticObject
{
public:
	Wall(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
	bool checkCollision(DynamicObject& other) const override;
	void handleCollision(DynamicObject& other) override;
};