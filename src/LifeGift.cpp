#include "LifeGift.h"
#include "Resources.h"
#include "Screen.h"

LifeGift::LifeGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen)
	: Gift(texture, scaleRatio, position), m_pacmanPtr(&screen.getPacmanPtr())
{}

void LifeGift::action()
{
	Resources::instance().playSound(LIFE_SOUND);
	m_pacmanPtr -> increaseLife();
}