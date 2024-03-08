#include "Controller.h"

void Controller::startGame()
{
	startInitializiation();

	m_file >> m_numOfRows; //read number of rows from the file for the 1st level

	int levelResult = 0; //the game hasn't been played yet

	while (!m_file.eof()) //if succeeded, continue reading from file the rest of level
	{
		if (levelResult == GAME_OVER) //check if levelResult = GAME_OVER to finish the game
			return showLosingWindow();

		prepareLevel();
		levelResult = m_screen.runLevel();

		while (levelResult == TIME_OUT)
		{
			repeatLevel();
			levelResult = m_screen.runLevel();
		}

		m_file >> m_numOfRows; //try to read number of rows from the file for the next level
	}

	if (levelResult == GAME_OVER) //check if player lost at the last level, in order to not show winning window
		showLosingWindow();

	else
		showWinningWindow();
}

void Controller::startInitializiation()
{
	m_screen.openGameWindow();
	m_screen.initializePacman();
}

void Controller::prepareLevel()
{
	m_file >> m_numOfCols;
	m_screen.prepareForLevel(m_numOfRows, m_numOfCols);
	m_screen.initializeDataMembers();
	readTxtFile();
	addObjectsToGame();
}

void Controller::repeatLevel()
{
	m_screen.prepareForLevel(m_numOfRows, m_numOfCols);
	m_screen.initializeDataMembers();
	m_screen.addTimeLimit(m_timeLimit);
	addObjectsToGame();
}

void Controller::readTxtFile()
{
	m_levelLines.clear();
	
	m_file.get(); //read \n from file after two numbers

	char object;
	m_file.get(object); //check it there's time limit for the level
	handleTimeLimit(object);

	auto line = std::string();

	for (int row = 0; row < m_numOfRows; row++)
	{
		if (std::getline(m_file, line))
			m_levelLines.push_back(line);

		else
			exit(EXIT_FAILURE);
	}
}

void Controller::addObjectsToGame()
{
	for (int row = 0; row < m_numOfRows; ++row)
		for (int col = 0; col < m_numOfCols; ++col)
			m_screen.addObjectsToGame(row, col, m_levelLines[row][col]);
}

void Controller::handleTimeLimit(const char charFromFile)
{
	if (charFromFile == 'T') //there's time limit in the level
	{
		m_file >> m_timeLimit;
		m_screen.addTimeLimit(m_timeLimit);
		m_file.get(); //read \n from file after the time limit
	}

	else //no time limit
		m_file.seekg(-1, m_file.cur); //move back in the file
}

void Controller::showLosingWindow()
{
	m_screen.closeGameWindow();
	Resources::instance().stopGameMusic();
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman-Lose");
	sf::Sprite losingSprite = sf::Sprite(Resources::instance().getTexture(LOSE_PIC));
	Resources::instance().playSound(LOSE_SOUND);

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		window.draw(losingSprite);
		window.display();
		waitForEvents(window);
	}
}

void Controller::showWinningWindow()
{
	m_screen.closeGameWindow();
	Resources::instance().stopGameMusic();
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(833, 747), "Pacman-Win");
	sf::Sprite winningSprite = sf::Sprite(Resources::instance().getTexture(WIN_PIC));
	Resources::instance().playSound(WIN_SOUND);

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		window.draw(winningSprite);
		window.display();
		waitForEvents(window);
	}
}

void Controller::waitForEvents(sf::RenderWindow& window) const
{
	if (auto event = sf::Event{}; window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;

			default:
				break;
			}
		}
	}
}