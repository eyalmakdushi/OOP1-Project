#include "Pacman.h"
#include "Resources.h"
#include "NormalState.h"
#include "SuperState.h"
#include "Screen.h"

Pacman::Pacman(const sf::Texture& normalTexture, const sf::Texture& superTexture,
				float scaleRatio, sf::Vector2f position, Screen& screen)

	: DynamicObject (normalTexture, scaleRatio, position), 
	  m_state(std::make_unique<NormalState>(screen)), m_screenPtr(&screen), m_currentSpeed(0), m_speedPerSecond(0),
	  m_superSprite(sf::Sprite(superTexture)), m_normalSprite(getSprite()), m_superTime(0.f)
{
	m_superSprite.setOrigin(getSprite().getOrigin());
}


// --------------------- set funcs: ---------------------
void Pacman::setScaleAndPosition(const float scaleRatio, const sf::Vector2f position)
{
	//scale
	changeSprite().setScale(scaleRatio, scaleRatio); //to keep proportions and fit into the screen
	m_superSprite.setScale(getSprite().getScale());
	m_currentSpeed = m_speedPerSecond = 240 * scaleRatio;

	//poistion
	changeSprite().setPosition(position);
	setStartPosition(position);
}

void Pacman::setSuper()
{
	m_superSprite.setPosition(getSprite().getPosition());
	changeSprite() = m_superSprite;
	m_state = std::make_unique <SuperState>();

	m_superClock.restart();
	m_superTime = m_superTimeRemaining += SUPER_TIMER;
}

void Pacman::setNormal()
{
	changeSprite().setTexture(Resources::instance().getTexture(pacman));
	m_state = std::make_unique <NormalState>(*m_screenPtr);
}

// --------------------- get funcs: ---------------------
const int Pacman::getScore() const
{
	return m_score;
}

const int Pacman::getLives() const
{
	return m_lives;
}

const int Pacman::getNumOfKeys() const
{
	return m_numOfKeys;
}


const sf::Vector2f* const Pacman::getPacmanPosition() const
{
	return getSpritePosition();
}

// --------------------- update funcs: ---------------------
void Pacman::prepareForNextLevel()
{
	m_numOfKeys = 0;
	setNormal(); //if pacman is super when finishing the previos level
}

void Pacman::faceRight()
{
	if (getSprite().getScale().x < 0)
		changeSprite().scale(-1, 1);

	changeSprite().setRotation(0.f);
}

void Pacman::increaseLife()
{
	++m_lives;
}

void Pacman::increaseScore(const size_t numOfDemons)
{
	m_score += DEMON_SCORE * int(numOfDemons);
}

void Pacman::decreaseLife()
{
	--m_lives;
}

void Pacman::decreaseNumOfKeys()
{
	--m_numOfKeys;
}

// --------------------- move funcs: ---------------------
void Pacman::move(const sf::Time deltaTime)
{
	if (m_superTimeRemaining > NO_TIME_LIMIT)
		m_superTimeRemaining = m_superTime - m_superClock.getSeconds();

	else
		setNormal();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_currentSpeed = m_speedPerSecond * 2;

	else 
		m_currentSpeed = m_speedPerSecond;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveUp();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveDown();

	else
		setDirection (sf::Vector2f(0, 0));

	setLastPosition(getSprite().getPosition());
	changeSprite().move(getDirection() * m_currentSpeed * deltaTime.asSeconds());
}

void Pacman::moveUp()
{
	if (getSprite().getScale().x < 0)
		changeSprite().scale(-1, 1);

	changeSprite().setRotation(-90.f);
	setDirection(sf::Vector2f(0, -1));
}

void Pacman::moveDown()
{
	if (getSprite().getScale().x < 0)
		changeSprite().scale(-1, 1);

	changeSprite().setRotation(90.f);
	setDirection(sf::Vector2f(0, 1));
}

void Pacman::moveBack()
{
	moveFromObstacle();
	Resources::instance().playSound(BUMP_SOUND);
}

// --------------------- handleCollision funcs: ---------------------
void Pacman::handleCollision(DynamicObject&)
{
	m_state -> handleDemonCollision(*this);
}

void Pacman::handleCollisionWithStatic(const Wall&)
{	
	moveBack();
}

void Pacman::handleCollisionWithStatic(Cookie& cookie)
{
	Resources::instance().playSound(COOKIE_SOUND);
	m_score += COOKIE_SCORE;
	cookie.dispose();
}

void Pacman::handleCollisionWithStatic(Door& door)
{
	m_state -> handleDoorCollision(*this, door);
}

void Pacman::handleCollisionWithStatic(Gift& gift)
{
	m_score += GIFT_SCORE;
	gift.action();
	gift.dispose();
}

void Pacman::handleCollisionWithStatic(Key& key)
{
	m_score += KEY_SCORE;
	++m_numOfKeys;
	Resources::instance().playSound(KEY_SOUND);
	key.dispose();
}