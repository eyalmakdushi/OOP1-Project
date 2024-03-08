#include "SuperState.h"
#include "Resources.h"

void SuperState::handleDoorCollision(Pacman&, Door& door)
{
    door.dispose();
    Resources::instance().playSound(KEY_SOUND);
}

void SuperState::handleDemonCollision(Pacman&)
{}