#pragma once
#include "StaticObject.h"
#include "Resources.h"

const int DOOR_SOUND = 13;
//---- class section ----
class Door : public StaticObject
{
public:
	Door (const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
	bool checkCollision(DynamicObject& other) const;
	void handleCollision(DynamicObject& other) override;
	void dispose() override;
};