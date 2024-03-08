#include "Menu.h"
#include "Resources.h"
#include "Play.h"
#include "Help.h"
#include "Exit.h"

Menu::Menu()
{
	m_menuBackground = sf::Sprite(Resources::instance().getTexture(MENU_BACKGROUND));

	m_buttons.push_back(std::make_unique <Play>(Resources::instance().getTexture(PLAY_NORMAL), 
												Resources::instance().getTexture(PLAY_HOVERED), m_window, WINDOW_WIDTH, 200));

	m_buttons.push_back(std::make_unique <Help>(Resources::instance().getTexture(HELP_NORMAL), 
												Resources::instance().getTexture(HELP_HOVERED), m_window, WINDOW_WIDTH, 
												WINDOW_HEIGHT / 2, Resources::instance().getTexture(HOW_TO_PLAY)));

	m_buttons.push_back(std::make_unique <Exit> (Resources::instance().getTexture(EXIT_NORMAL), 
												 Resources::instance().getTexture(EXIT_HOVERED), m_window, WINDOW_WIDTH, 700));
}

void Menu::displayMenu()
{
	Resources::instance().playMenuMusic();
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman-Menu");

	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::White);
		draw();
		m_window.display();
		waitForEvents();
	}
}

void Menu::draw()
{
	m_window.draw(m_menuBackground);

	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
		m_buttons[i] -> draw(m_window);
}

void Menu::waitForEvents()
{
	if (auto event = sf::Event{}; m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{

			case sf::Mouse::Button::Left:
				leftButton(event);
				break;
			}

			break;

		case sf::Event::MouseMoved:
			mouseMoved();
			break;

		case sf::Event::KeyPressed:
			keyPressed(event);
			break;
			
		}
	}
}

void Menu::leftButton(sf::Event& event)
{
	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
		if (m_buttons[i]->checkLocation(location))
		{
			Resources::instance().playSound(BUTTON_SOUND);
			m_buttons[i]->reactToClick();
		}
}

void Menu::mouseMoved()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
	sf::Vector2f location = m_window.mapPixelToCoords(pixelPos);

	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
		m_buttons[i]->setHoveredSprite(location);
}

void Menu::keyPressed(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Enter:
		Resources::instance().playSound(BUTTON_SOUND);
		m_buttons[0]->reactToClick(); //play
		break;

	case sf::Keyboard::Escape:
		Resources::instance().playSound(BUTTON_SOUND);
		m_window.close();
		break;
	}
}
