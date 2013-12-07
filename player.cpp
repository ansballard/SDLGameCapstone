#include "player.h"

void Player::playerJump()
{
    if(vSpeed == 0)
    {
        vSpeed = -5;
        this->clearCollDown();
    }
}
