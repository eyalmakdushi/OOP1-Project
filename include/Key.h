#pragma once
#include "StaticObject.h"

class Key : public StaticObject
{
public:
	Key(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
	void handleCollision(DynamicObject& other) override;
};