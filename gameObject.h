#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// COLLISION STATIC CONSTS
static const int COLL_NONE = 0;
static const int COLL_UP = 1;
static const int COLL_RIGHT = 2;
static const int COLL_DOWN = 3;
static const int COLL_LEFT = 4;
static const int COLL_IN = 5;

// SPRITE ANIMATION STATIC CONSTS

static const int XSTILL_RIGHT = 0;
static const int XMOVING_RIGHT = 1;
static const int XSTILL_LEFT = 2;
static const int XMOVING_LEFT = 3;
static const int LEFT_BOUND = 0;
static const int RIGHT_BOUND = 640;

class GameObject
{
    protected:
        bool facingRight; // is GameObject facing right or not
        int horizontalMovement; // is GameObject moving left(-1), right(1), or still(0)
        int verticalMovement; // is GameObject moving down(-1), up(1), or still(0)
        SDL_Texture *image;
        SDL_Rect **spriteSheet; // 2D dynamic array of images as sprite sheet
        int xNumSprites; // number of sprites in sheet via x
        int yNumSprites; // number of sprites in sheet via y
        int spriteWidth;
        int spriteHeight;
        int xPos;
        int yPos;
        int hSpeed; // horizontal speed
        double vSpeed;
        bool collUp; // object is: 0 none, 1 above, 2 to the right, 3 below, 4 to the left, 5 for inside
        bool collDown;
        bool collLeft;
        bool collRight;
        int startTicks;
        int currentTicks;

    public:
        // CONSTRUCTOR
        GameObject(const GameObject& that); // copy constructor
        GameObject(bool facingRightParam, int horizontalMovementParam, int verticalMovementParam, int xPosParam, int yPosParam, int hSpeedParam, int vSpeedParam);
        GameObject(SDL_Texture *imageParam, int xPosParam, int yPosParam, int widthParam, int heightParam);

        //DESTRUCTOR
        virtual ~GameObject();

        // GETTERS
        int getHorizontalMovement() {return horizontalMovement;}
        int getVerticalMovement() {return verticalMovement;}
        bool getFacingRight() {return facingRight;} // facing right return true else false
        int getXNumSprites() {return xNumSprites;}
        int getYNumSprites() {return yNumSprites;}
        int getSpriteWidth() {return spriteWidth;}
        int getSpriteHeight() {return spriteHeight;}
        int getXPos() {return xPos;}
        int getYPos() {return yPos;}
        int getHSpeed() {return hSpeed;} // get horizontal speed
        double getVSpeed() {return vSpeed;}
        SDL_Texture* getImage() {return image;} // get pointer to original image object
        SDL_Rect** getSpriteSheet(); // return copy of sprite sheet (not pointer to original)
        SDL_Rect* getSprite(); // return sprite according to in-class clips and ticks
        SDL_Rect* getSprite(int x, int y) {return &spriteSheet[x][y];} // return specific sprite from sheet given x and y
        bool isMovingHorizontal() {return (horizontalMovement != 0);} // true if horizontal movement isn't 0
        bool isMovingVertical() {return (verticalMovement != 0);}

        // SETTERS
        void setHorizontalMovement(int hMove); // sets horizontal movement as well as facing right
        void setVerticalMovement(int vMove) {verticalMovement = vMove;}
        void setFacingRight(bool fRight) {facingRight = fRight;}
        void setSprite(SDL_Rect **sSheet, int xNumSpritesParam, int yNumSpritesParam); // set sprite sheet (not a pointer to parameter sheet)
        void setSprite(SDL_Texture *image, int xNumSpritesParam, int yNumSpritesParam, int spriteWidthParam, int spriteHeightParam); // take image, fill array with sprites via measurements
        bool moveSpriteHorizontal();
        bool moveSpriteHorizontal(int ticks);
        bool moveSpriteVertical();
        bool moveSprite(int ticks) {moveSpriteHorizontal(ticks);moveSpriteVertical();}
        void clearCollision() {collUp = false; collDown = false; collLeft = false; collRight = false;}
        void clearCollDown() {collDown = false;}
        void setXPos(int xPosParam) {xPos = xPosParam;}
        void setYPos(int yPosParam) {yPos = yPosParam;}
        void copyAll(GameObject* that);

        // COLLISION
        int objectCollisionCheck(GameObject *that);
        void objectCollisionCheck(GameObject **that, int listSize);

        // DISPLAY
        void collisionDisplay() {std::cout << collUp << " " << collDown << " " << collLeft << " " << collRight << "\n";}
        void display() {std::cout << "Does Exist" << std::endl;}
        void displayTopLeft() {std::cout << "("<<xPos<<","<<yPos<<")\n";}

        // OPERATORS
        void operator=(GameObject* that);
};

#endif // GAMEOBJECT_H
