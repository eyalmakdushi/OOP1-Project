#pragma once
#include "StaticObject.h"

//---- class section ----
class Cookie : public StaticObject
{
public:
	Cookie(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);

	//collision funcs:
	void handleCollision(DynamicObject& other) override;	
	void dispose() override;

	//counter funcs:
	static int getCookieCount();
	static void nullifyCookies();

private:
	static int m_cookieCounter;
};