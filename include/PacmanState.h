#pragma once
#include "Pacman.h"
#include "Door.h"

class PacmanState
{
public:
    virtual ~PacmanState() = default;
    virtual void handleDoorCollision(Pacman& pacman, Door& door) = 0;
    virtual void handleDemonCollision(Pacman& pacman) = 0;
};