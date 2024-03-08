#include <thread>
#include "Resources.h"
#include "NormalState.h"

NormalState::NormalState (Screen& screen)
	: m_screenPtr(&screen)
{}

void NormalState::handleDoorCollision(Pacman& pacman, Door& door)
{
	if (pacman.getNumOfKeys() > 0)
	{
		door.dispose();
		pacman.decreaseNumOfKeys();
	}

	else
		pacman.moveBack();
}

void NormalState::handleDemonCollision(Pacman& pacman)
{
	Resources::instance().playSound(DEMON_SOUND);
	pacman.decreaseLife();
	pacman.resetPosition();
	m_screenPtr -> resetDemonsPosition();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}