#include "Screen.h"
#include "TimeGift.h"

TimeGift::TimeGift(const sf::Texture & texture, float scaleRatio, sf::Vector2f position, Screen& screen)
	: Gift (texture, scaleRatio, position), m_screenPtr(&screen)
{}

void TimeGift::action()
{
	Resources::instance().playSound(TIME_SOUND);
	m_screenPtr -> addTimeLimit(20);
}