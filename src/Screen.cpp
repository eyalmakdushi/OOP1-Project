#include <thread>
#include "Screen.h"

Screen::Screen()
	: m_board(this), m_frozen(NO_TIME_LIMIT), m_remainingFrozen(NO_TIME_LIMIT), m_timeLimit(NO_TIME_LIMIT), m_remainingTime(NO_TIME_LIMIT)
{}

void Screen::openGameWindow()
{
	m_window.setFramerateLimit(60);
	m_window.create(sf::VideoMode(SCREEN_EDGE_SIZE, SCREEN_EDGE_SIZE + INFORMATION_BAR_HEIGHT), "Pacman-Game");
}

float Screen::getTimeLimit() const
{
	return m_timeLimit;
}

Pacman& Screen::getPacmanPtr()
{
	return *m_pacmanPtr;
}

void Screen::initializePacman()
{
	m_pacmanPtr = std::make_unique<Pacman>(Resources::instance().getTexture(pacman), Resources::instance().getTexture(superPacman),
											0.f, sf::Vector2f(), *this);
}

//calling board funcs
void Screen::prepareForLevel(const int rows, const int cols)
{
	m_pacmanPtr -> prepareForNextLevel();
	m_demonsVec.clear();
	m_board.prepareBoardForLevel(rows, cols);
}

void Screen::addObjectsToGame(const int row, const int col, const char object)
{
	auto position = calculatePosition(row, col);

	switch (object)
	{
	case (EMPTY):
		return;

	case (PACMAN):
		m_pacmanPtr -> setScaleAndPosition(m_board.getScaleRatio(), position);
		return;

	case(DEMON):
		m_demonsVec.push_back(Demon(Resources::instance().getTexture(demon), m_board.getScaleRatio(), position, *m_pacmanPtr));
		return;
	}

	m_board.addObjectToBoard(row, col, object, position);
}

sf::Vector2f Screen::calculatePosition(const int row, const int col) const
{
	sf::Vector2f position; //set to center of sprite after scaling, according to position in the game (row & col)

	auto numOfRows = m_board.getRows();
	auto numOfCols = m_board.getCols();
	auto scaleRatio = m_board.getScaleRatio();

	position.x = float(SCREEN_EDGE_SIZE) / numOfRows * col + IMAGE_EDGE_SIZE * scaleRatio / 2;
	position.y = float(SCREEN_EDGE_SIZE) / numOfCols * row + IMAGE_EDGE_SIZE * scaleRatio / 2;

	if (numOfRows > numOfCols)
		position.y = (float(SCREEN_EDGE_SIZE) / numOfRows) * row + IMAGE_EDGE_SIZE * scaleRatio / 2;

	else if (numOfCols > numOfRows)
		position.x = (float(SCREEN_EDGE_SIZE) / numOfCols) * col + IMAGE_EDGE_SIZE * scaleRatio / 2;

	return position;
}

void Screen::initializeDataMembers()
{
	m_firstKeyPressed = false;
	m_pacmanPtr -> faceRight();
	m_frozen = m_remainingFrozen = m_remainingTime = m_timeLimit = NO_TIME_LIMIT;
	Cookie::nullifyCookies();
}

void Screen::addTimeLimit(const float timeLimit)
{
	m_timeLimit += timeLimit;
}

int Screen::runLevel()
{
	m_levelClock.restart();

	while (m_window.isOpen())
	{
		manageWindow();
		
		if (m_firstKeyPressed)
			manageBoard();

		if (Cookie::getCookieCount() == FINISH)
			return wonLevel();

		if (m_pacmanPtr -> getLives() == FINISH)
			return gameOver();

		if (m_remainingTime < NO_TIME_LIMIT)
			return timeOut();
	}

	return 42; //never reached, to avoid Warning C4715 not all control paths return a value
}

void Screen::manageWindow()
{
	m_window.clear(sf::Color::White);
	draw();
	m_window.display();
	pollEvent();
}

void Screen::manageBoard()
{
	moveFigures();
	handleCollisions();
	m_board.removeDisposedObjects();
}

//----------------- window funcs: -----------------
void Screen::draw()
{
	m_board.draw(m_window);

	for (auto& demon : m_demonsVec)
		demon.draw(m_window);

	m_pacmanPtr->draw(m_window);

	m_window.draw(prepareInformation());
}

sf::Text Screen::prepareInformation()
{
	//prepare string
	auto information = "Level: " + std::to_string(m_levelNumber);
	information += "\tTime elapsed: " + std::to_string(int(m_levelClock.getSeconds()));
	information += "\tLives: " + std::to_string(m_pacmanPtr->getLives());
	information += "\tScore: " + std::to_string(m_pacmanPtr->getScore());
	information += "\tKeys: " + std::to_string(m_pacmanPtr->getNumOfKeys());
	
	if (m_timeLimit != NO_TIME_LIMIT && m_firstKeyPressed)
	{
		m_remainingTime = m_timeLimit - m_timeLimitClock.getSeconds();
		information = information + "\tTime remaining: " + std::to_string(int(m_remainingTime));
	}

	//prepare text
	auto result = sf::Text(information, m_font, 20u);
	result.setFillColor(sf::Color::Black);
	result.setPosition(float(SCREEN_EDGE_SIZE) / 2, float(SCREEN_EDGE_SIZE) + float(INFORMATION_BAR_HEIGHT) / 2);
	result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);

	return result;
}

void Screen::pollEvent()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			Resources::instance().stopGameMusic();
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed:
			if (!m_firstKeyPressed)
			{
				m_firstKeyPressed = true;
				m_timeLimitClock.restart();
				m_moveClock.restart();
			}
			break;
		}
	}
}

//----------------- board funcs: -----------------
void Screen::moveFigures()
{
	const auto deltaTime = m_moveClock.restart();
	
	m_pacmanPtr->move(deltaTime);

	if (m_remainingFrozen > NO_TIME_LIMIT)
		m_remainingFrozen = m_frozen - m_frozenDemonsClock.getSeconds();

	else
		for (auto& demon : m_demonsVec)
		{
			demon.normalSprite();
			demon.move(deltaTime);
		}
}

void Screen::handleCollisions()
{
	//dynamic & static collisions
	m_board.handleCollisions(*m_pacmanPtr);

	for (auto& demon : m_demonsVec)
		m_board.handleCollisions(demon);

	//demon & pacman collision
	for (auto& demon : m_demonsVec)
		if (demon.checkCollision(*m_pacmanPtr))
			demon.handleCollision(*m_pacmanPtr);
}

void Screen::freezeDemons()
{
	Resources::instance().playSound(FREEZE_SOUND);
	m_frozenDemonsClock.restart();

	m_frozen = m_remainingFrozen += FREEZING_TIMER;

	for (auto& demon : m_demonsVec)
		demon.frozenSprite();
}

void Screen::resetDemonsPosition()
{
	for (auto& demon : m_demonsVec)
		demon.resetPosition();

	m_firstKeyPressed = false;
}

int Screen::wonLevel()
{
	Resources::instance().playSound(HOORAY_SOUND);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	++m_levelNumber;
	m_pacmanPtr->increaseScore(m_demonsVec.size());
	return OUT_OF_COOKIES;
}

int Screen::gameOver()
{
	m_window.close();
	Resources::instance().stopGameMusic();
	return GAME_OVER;
}

int Screen::timeOut()
{
	Resources::instance().playSound(TIME_OUT_SOUND);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	m_pacmanPtr -> decreaseLife();
	return TIME_OUT;
}

void Screen::closeGameWindow()
{
	m_window.close();
}