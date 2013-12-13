#ifndef NPC_H
#define NPC_H

#include <SDL.h>
#include <SDL_image.h>
#include "gameObject.h"

class NPC : public GameObject
{
private:
    int rangeRight;
    int rangeLeft;
    int initialPosX;
    bool isAlive;

public:
    // CONSTRUCTORS
    NPC(bool facingRightParam, int horizontalMovementParam, int verticalMovementParam, int xPosParam, int yPosParam, int hSpeedParam, int vSpeedParam) : GameObject(facingRightParam, horizontalMovementParam, verticalMovementParam, xPosParam, yPosParam, hSpeedParam, vSpeedParam){isAlive = true;}
    NPC(const NPC& that) : GameObject(that){}
    NPC(SDL_Texture *imageParam, int xPosParam, int yPosParam, int widthParam, int heightParam) : GameObject(imageParam, xPosParam, yPosParam, widthParam, heightParam) {}

    // MOVEMENT
    void setRange(int rangeRight, int rangeLeft);
    int getRangeRight();
    int getRangeLeft();
    int getInitialPosX();
    bool getIsAlive();

    // ANIMATION
    void die();

};

#endif
