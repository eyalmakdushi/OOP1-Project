#pragma once
#include "PacmanState.h"
#include "Screen.h"

class NormalState : public PacmanState
{
public:
    NormalState(Screen& screen);
    void handleDoorCollision(Pacman& pacman, Door&) override;
    void handleDemonCollision(Pacman& pacman) override;

private:
    Screen* m_screenPtr = nullptr;
};