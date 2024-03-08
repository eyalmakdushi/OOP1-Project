#include "SuperGift.h"
#include "Resources.h"
#include "Screen.h"

SuperGift::SuperGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen)
	: Gift(texture, scaleRatio, position), m_pacmanPtr (&screen.getPacmanPtr())
{}

void SuperGift::action()
{
	Resources::instance().playSound(SUPER_SOUND);
	m_pacmanPtr -> setSuper();
}