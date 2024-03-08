#pragma once
#include "Gift.h"

class Screen;

//---- class section ----
class FreezeGift : public Gift
{
public:
	FreezeGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen& screen);
	void action() override;

private:
	Screen* m_screenPtr = nullptr;
};