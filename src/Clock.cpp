#include "Clock.h"

float Clock::getSeconds() const
{
    return m_clock.getElapsedTime().asSeconds();
}

sf::Time Clock::getElapsedTime() const
{
    return m_clock.getElapsedTime();
}

sf::Time Clock::restart()
{
    return m_clock.restart();
}