#pragma once
#include "Gift.h"
#include "Pacman.h"

//---- class section ----
class SuperGift : public Gift
{
public:
	SuperGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen);
	void action() override;

private:
	Pacman* m_pacmanPtr;
};