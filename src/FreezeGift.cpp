#include "Screen.h"
#include "FreezeGift.h"

FreezeGift::FreezeGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen)
	: Gift(texture, scaleRatio, position), m_screenPtr(&screen)
{}

void FreezeGift::action()
{
	m_screenPtr -> freezeDemons();
}