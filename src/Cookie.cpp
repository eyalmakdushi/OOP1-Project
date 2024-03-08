#include "Cookie.h"

int Cookie::m_cookieCounter = 0;

Cookie::Cookie(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
	: StaticObject(texture, scaleRatio, position)
{
	++m_cookieCounter;
}

void Cookie::nullifyCookies()
{
	m_cookieCounter = 0;
}

void Cookie::handleCollision(DynamicObject& other)
{
	other.handleCollisionWithStatic(*this);
}

void Cookie::dispose()
{
	setDisposed();
	--m_cookieCounter;
}

int Cookie::getCookieCount()
{
	return m_cookieCounter;
}