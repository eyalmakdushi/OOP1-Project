#pragma once
#include <SFML/Graphics.hpp>

const float NO_TIME_LIMIT = 0;

class Clock
{
public:
    sf::Time getElapsedTime() const;
    float getSeconds() const;
    sf::Time restart();

private:
    sf::Clock m_clock;
};