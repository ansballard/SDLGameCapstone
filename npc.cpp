#include "npc.h"

// GETTERS
//////////
int NPC::getRangeRight()
{
    return rangeRight;
}
int NPC::getRangeLeft()
{
    return rangeLeft;
}
int NPC::getInitialPosX()
{
    return initialPosX;
}
bool NPC::getIsAlive()
{
    return isAlive;
}

// MOVEMENT
///////////
void NPC::setRange(int rangeRight, int rangeLeft)
{
    isAlive = true;
    initialPosX = xPos;
    this->rangeRight = rangeRight;
    this->rangeLeft = rangeLeft;
}

// ANIMATIONS
/////////////
void NPC::die()
{

    isAlive = false;
}
