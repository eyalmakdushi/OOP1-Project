#include "Button.h"
#include "Resources.h"

Button::Button(const sf::Texture& normalTexture, const sf::Texture& hoveredTexture, sf::RenderWindow& window,
				const float xCoord, const float yCoord)

	: m_normalSprite(sf::Sprite(normalTexture)), m_hoveredSprite(sf::Sprite(hoveredTexture)), m_window(window)
{
	m_normalSprite.setOrigin(sf::Vector2f(m_normalSprite.getTexture()->getSize() / 2u));
	m_hoveredSprite.setOrigin(sf::Vector2f(m_hoveredSprite.getTexture()->getSize() / 2u));

	m_rect = sf::RectangleShape(sf::Vector2f(m_normalSprite.getTexture()->getSize()));
	m_rect.setOrigin(m_normalSprite.getOrigin());
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(3);
	m_rect.setOutlineColor(sf::Color::Black);

	m_normalSprite.setPosition(xCoord / 2, yCoord);
	m_hoveredSprite.setPosition(xCoord / 2, yCoord);
	m_rect.setPosition(xCoord / 2, yCoord);

	m_drawingSprite = m_normalSprite;
}

void Button::closeWindow()
{
	m_window.close();
}

void Button::showHowToPlay(const sf::Sprite howToPlay)
{
	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::White);
		m_window.draw(howToPlay);
		m_window.display();
		if (waitForEvent())
		{
			m_drawingSprite = m_normalSprite;
			return;
		}
	}
}

bool Button::waitForEvent()
{
	if (auto event = sf::Event{}; m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			return true;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				Resources::instance().playSound(BUTTON_SOUND);
				return true;
			}

		default:
			return false;
		}
	}

	else
		return false;
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_drawingSprite);
	window.draw(m_rect);
}

void Button::showMenu()
{
	m_window.create(sf::VideoMode(800, 900), "Pacman-Menu");
}

bool Button::checkLocation(const sf::Vector2f& location) const
{
	return m_hoveredSprite.getGlobalBounds().contains(location);
}

void Button::setHoveredSprite(const sf::Vector2f& location)
{
	if (m_normalSprite.getGlobalBounds().contains(location))
		m_drawingSprite = m_hoveredSprite;

	else
		m_drawingSprite = m_normalSprite;
}