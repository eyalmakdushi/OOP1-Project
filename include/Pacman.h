//---- include section ----
#pragma once
#include <memory>
#include "DynamicObject.h"
#include "Wall.h"
#include "Cookie.h"
#include "Door.h"
#include "Gift.h"
#include "Key.h"
#include "Clock.h"

class Screen;
class PacmanState;

//---- const section ---- 
const int COOKIE_SCORE = 2;
const int GIFT_SCORE = 5;
const int KEY_SCORE = 7;
const int FINISH_LEVEL_SCORE = 50;
const int DEMON_SCORE = 2;

const int KEY_SOUND = 3;
const int BUMP_SOUND = 4;
const int COOKIE_SOUND = 5;
const int DEMON_SOUND = 6;
const int LIFE_SOUND = 7;
const int SUPER_SOUND = 9;

const float SUPER_TIMER = 7;

//---- class section ----
class Pacman : public DynamicObject
{
public:
	Pacman(const sf::Texture& normalTexture, const sf::Texture& superTexture, 
			float scaleRatio, sf::Vector2f position, Screen& screen);

	// --------------------- set funcs: ---------------------
	void setScaleAndPosition(const float scaleRatio, const sf::Vector2f position);
	void setSuper();
	
	// --------------------- get funcs: ---------------------
	const int getScore() const;
	const int getLives() const;
	const int getNumOfKeys() const;
	const sf::Vector2f* const getPacmanPosition() const;

	// --------------------- update funcs: ---------------------
	void prepareForNextLevel();
	void move(sf::Time) override;
	void increaseLife();
	void increaseScore(const size_t numOfDemons);
	void decreaseLife();
	void decreaseNumOfKeys();
	void moveBack();
	void faceRight();

	//collision funcs:
	void handleCollision(DynamicObject& other) override;
	void handleCollisionWithStatic(const Wall&) override;
	void handleCollisionWithStatic(Cookie& cookie) override;
	void handleCollisionWithStatic(Door&) override;
	void handleCollisionWithStatic(Gift& gift) override;
	void handleCollisionWithStatic(Key& key) override;

private:
	void setNormal();

	float m_speedPerSecond;
	float m_currentSpeed;
	sf::Sprite m_superSprite;
	sf::Sprite m_normalSprite;

	Clock m_superClock;
	float m_superTime, m_superTimeRemaining = NO_TIME_LIMIT;

	int m_score = 0;
	int m_lives = 3;
	std::unique_ptr<PacmanState> m_state;
	Screen* m_screenPtr = nullptr;
	int m_numOfKeys = 0;

	void moveUp() override;
	void moveDown() override;
};