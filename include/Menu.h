#pragma once
#include <vector>
#include <memory>
#include "Button.h"

//---- const section ----
const int HELP_NORMAL = 11;
const int HELP_HOVERED = 12;
const int PLAY_NORMAL = 13;
const int PLAY_HOVERED = 14;
const int EXIT_NORMAL = 15;
const int EXIT_HOVERED = 16;
const int MENU_BACKGROUND = 17;
const int HOW_TO_PLAY = 18;

const int NUMBER_OF_BUTTONS = 3;

class Menu
{
public:
    Menu();
    Menu(const Menu&) = delete;
    void operator = (const Menu&) = delete;
    void displayMenu();

private:
    void draw();
    void waitForEvents();
    void keyPressed(sf::Event& event);
    void mouseMoved();
    void leftButton(sf::Event& event);

    sf::RenderWindow m_window;
    sf::Sprite m_menuBackground;
    std::vector <std::unique_ptr <Button>> m_buttons;
};