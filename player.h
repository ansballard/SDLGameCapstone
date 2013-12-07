#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "gameObject.h"

class Player : public GameObject
{
private:
    bool jumping;

public:
    // CONSTRUCTORS
    Player(bool facingRightParam, int horizontalMovementParam, int verticalMovementParam, int xPosParam, int yPosParam, int hSpeedParam, int vSpeedParam) : GameObject(facingRightParam, horizontalMovementParam, verticalMovementParam, xPosParam, yPosParam, hSpeedParam, vSpeedParam){}
    Player(const Player& that) : GameObject(that){}
    Player(SDL_Texture *imageParam, int xPosParam, int yPosParam, int widthParam, int heightParam) : GameObject(imageParam, xPosParam, yPosParam, widthParam, heightParam) {}

    // MOVEMENT
    void playerJump();
};

#endif
