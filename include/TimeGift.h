#pragma once
#include "Gift.h"

class Screen;

const int TIME_SOUND = 10;

//---- class section ----
class TimeGift : public Gift
{
public:
	TimeGift(const sf::Texture& texture, float scaleRatio, sf::Vector2f position, Screen&);
	void action() override;

private:
	Screen* m_screenPtr = nullptr;
};