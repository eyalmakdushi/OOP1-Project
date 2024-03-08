#pragma once
#include "PacmanState.h"

class SuperState : public PacmanState
{
public:
    void handleDoorCollision(Pacman& pacman, Door& door) override;
    void handleDemonCollision(Pacman& pacman) override;
};