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
void NPC::setRange(int rangeLeft, int rangeRight)
{
    isAlive = true;
    initialPosX = xPos;
    this->rangeRight = rangeRight;
    this->rangeLeft = rangeLeft;
}

void NPC::setHorizontalMovement()
{
    if(facingRight)
    {
        if(xPos < rangeRight)
            horizontalMovement = 1;
        else
        {
            facingRight = false;
            horizontalMovement = -1;
        }
    }
    else
    {
        if(xPos > rangeLeft)
            horizontalMovement = -1;
        else
        {
            facingRight = true;
            horizontalMovement = 1;
        }
    }
}

bool NPC::moveSpriteHorizontal(int ticks) // true for movement, false for none
{
    setHorizontalMovement();
    currentTicks = ticks;
    GameObject::moveSpriteHorizontal();
}

// ANIMATIONS
/////////////
void NPC::die()
{

    isAlive = false;
}
