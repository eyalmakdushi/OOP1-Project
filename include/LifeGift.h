#pragma once
#include "Gift.h"
#include "Pacman.h"

//---- class section ----
class LifeGift : public Gift
{
public:
	LifeGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen);
	void action() override;

private:
	Pacman* m_pacmanPtr;
};