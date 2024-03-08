#pragma once
#include "StaticObject.h"

//---- class section ----
class Gift : public StaticObject
{
public:
	Gift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
	void handleCollision(DynamicObject& other) override;
	virtual void action() = 0;
};