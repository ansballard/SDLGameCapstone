#include "gameObject.h"

// CONSTRUCTORS
///////////////
GameObject::GameObject(bool facingRightParam, int horizontalMovementParam, int verticalMovementParam, int xPosParam, int yPosParam, int hSpeedParam, int vSpeedParam)
{
    facingRight = facingRightParam;
    horizontalMovement = horizontalMovementParam;
    verticalMovement = verticalMovementParam;
    xPos = xPosParam;
    yPos = yPosParam;
    hSpeed = hSpeedParam;
    vSpeed = vSpeedParam;
    collUp = 0;
    collDown = 0;
    collLeft = 0;
    collRight = 0;
    spriteSheet = NULL;
}

GameObject::GameObject(const GameObject& that) // copy constructor
{
    facingRight = that.facingRight;
    horizontalMovement = that.horizontalMovement;
    verticalMovement = that.verticalMovement;
    xNumSprites = that.xNumSprites;
    yNumSprites = that.yNumSprites;
    spriteWidth = that.spriteWidth;
    spriteHeight = that.spriteHeight;
    vSpeed = that.vSpeed;
    setSprite(that.spriteSheet, xNumSprites, yNumSprites);
    collUp = that.collUp;
    collDown = that.collDown;
    collLeft = that.collLeft;
    collRight = that.collRight;
}

GameObject::GameObject(SDL_Texture *imageParam, int xPosParam, int yPosParam, int widthParam, int heightParam)
{
    image = imageParam;
    xPos = xPosParam;
    yPos = yPosParam;
    spriteWidth = widthParam;
    spriteHeight = heightParam;
    spriteSheet = NULL;
}

// DESTRUCTOR
/////////////
GameObject::~GameObject()
{
    if(spriteSheet != NULL)
    {
        for(int i = 0; i < xNumSprites; i++)
        {
            delete [] spriteSheet[i];
            spriteSheet[i] = NULL;
        }
        delete [] spriteSheet;
        spriteSheet = NULL;
    }
    delete image;
    image = NULL;
}

// GETTERS
//////////
SDL_Rect* GameObject::getSprite()
{
    //int useClipA = useClip%p1->getXNumSprites();
    //int useClipB = useClip/p1->getXNumSprites();
    //return &spriteSheet[x][y];

    if(horizontalMovement == 0)
    {
        if(facingRight == false)
        {
            return &spriteSheet[XSTILL_LEFT%xNumSprites][XSTILL_LEFT/xNumSprites];
        }
        else
        {
            return &spriteSheet[XSTILL_RIGHT%xNumSprites][XSTILL_RIGHT/xNumSprites];
        }
    }
    else if((currentTicks - startTicks) % 250 < 126)
    {
        if(horizontalMovement > 0)
        {
            return &spriteSheet[XMOVING_RIGHT%xNumSprites][XMOVING_RIGHT/xNumSprites];
        }
        else
        {
            return &spriteSheet[XMOVING_LEFT%xNumSprites][XMOVING_LEFT/xNumSprites];
        }
    }
    else
    {
        if(horizontalMovement > 0)
        {
            return &spriteSheet[XSTILL_RIGHT%xNumSprites][XSTILL_RIGHT/xNumSprites];
        }
        else
        {
            return &spriteSheet[XSTILL_LEFT%xNumSprites][XSTILL_LEFT/xNumSprites];
        }
    }
}

// COMPLICATED SPRITE GETTER
////////////////////////////
SDL_Rect** GameObject::getSpriteSheet()
{
    SDL_Rect **temp;

    temp = new SDL_Rect*[yNumSprites];
    for(int i = 0; i < yNumSprites; i++)
    {
        temp[i] = new SDL_Rect[xNumSprites];
        for(int j = 0; j < xNumSprites; j++)
        {
            temp[i][j].x = i * spriteWidth;
            temp[i][j].y = j * spriteHeight;
            temp[i][j].w = spriteWidth;
            temp[i][j].h = spriteHeight;
        }
    }

    return temp;
}

// SETTERS
//////////
void GameObject::setHorizontalMovement(int hMove) // sets horizontalMovement and facingRight based off it
{
    horizontalMovement = hMove;
    if(horizontalMovement > 0)
        facingRight = true;
    else if(horizontalMovement < 0)
        facingRight = false;
}

void GameObject::setSprite(SDL_Rect **sSheet, int xNumSpritesParam, int yNumSpritesParam)
{
    SDL_Rect **temp;

    temp = new SDL_Rect*[yNumSprites];
    for(int i = 0; i < yNumSprites; i++)
    {
        temp[i] = new SDL_Rect[xNumSprites];
        for(int j = 0; j < xNumSprites; j++)
        {
            temp[i][j].x = sSheet[i][j].x;
            temp[i][j].y = sSheet[i][j].y;
            temp[i][j].w = sSheet[i][j].w;
            temp[i][j].h = sSheet[i][j].h;
        }
    }

    spriteSheet = temp;
}

void GameObject::setSprite(SDL_Texture *imageParam, int xNumSpritesParam, int yNumSpritesParam, int spriteWidthParam, int spriteHeightParam)
{
    xNumSprites = xNumSpritesParam;
    yNumSprites = yNumSpritesParam;
    spriteWidth = spriteWidthParam;
    spriteHeight = spriteHeightParam;
    spriteHeight = spriteHeightParam;
    image = imageParam;

    spriteSheet = new SDL_Rect*[yNumSprites];
    for(int i = 0; i < yNumSprites; i++)
    {
        spriteSheet[i] = new SDL_Rect[xNumSprites];
        for(int j = 0; j < xNumSprites; j++)
        {
            spriteSheet[i][j].x = i * spriteWidth;
            spriteSheet[i][j].y = j * spriteHeight;
            spriteSheet[i][j].w = spriteWidth;
            spriteSheet[i][j].h = spriteHeight;
        }
    }
}

void GameObject::copyAll(GameObject* that)
{
    facingRight = that->facingRight;
    horizontalMovement = that->horizontalMovement;
    verticalMovement = that->verticalMovement;
    xNumSprites = that->xNumSprites;
    yNumSprites = that->yNumSprites;
    spriteWidth = that->spriteWidth;
    spriteHeight = that->spriteHeight;
    xPos = that->xPos;
    yPos = that->yPos;
    vSpeed = that->vSpeed;
    if(that->spriteSheet != NULL)
        setSprite(that->spriteSheet, xNumSprites, yNumSprites);
    collUp = that->collUp;
    collDown = that->collDown;
    collLeft = that->collLeft;
    collRight = that->collRight;

}

int GameObject::objectCollisionCheck(GameObject *that) // 0 for none, 1 for top, 2 for right, 3 for bottom, 4 for left, 5 for inside
{
    if((xPos + spriteWidth < that->getXPos() || xPos > that->getXPos() + that->getSpriteWidth()) || ((yPos > that->getYPos() + that->getSpriteHeight()) || yPos + spriteHeight < that->getYPos()))
        return 0;

    else if(yPos+spriteHeight <= that->getYPos()*1.0 + 0.5*that->getSpriteHeight())
    {
        collDown = true;
        this->setYPos(that->getYPos() - getSpriteHeight());
    }
    else if(yPos >= (that->getYPos()*1.0 + 0.5*that->getSpriteHeight()))
    {
        collUp = true;
        this->setYPos(that->getSpriteHeight() + that->getYPos());
    }
    else if(xPos + spriteWidth <= that->getXPos()*1.0 + that->getSpriteWidth()*0.1)
    {
        collRight = true;
    }
    else if(xPos >= that->getXPos()*1.0 + 0.5*that->getSpriteWidth())
    {
        collLeft = true;
    }
    else
        return -1;
    return 1;
}

bool GameObject::moveSpriteHorizontal() // true for movement, false for none
{
    if((horizontalMovement < 0 && !collLeft) || (horizontalMovement > 0 && !collRight))
    {
        xPos += horizontalMovement * hSpeed;
        return true;
    }
    else
        return false;
}

bool GameObject::moveSpriteHorizontal(int ticks) // true for movement, false for none
{
    currentTicks = ticks;
    if((horizontalMovement < 0 && !collLeft && xPos > LEFT_BOUND) || (horizontalMovement > 0 && !collRight && xPos + spriteWidth < RIGHT_BOUND))
    {
        xPos += horizontalMovement * hSpeed;
        return true;
    }
    else if(horizontalMovement == 0)
    {
        startTicks = currentTicks;
        return false;
    }
    else
    {
        return false;
    }
}

bool GameObject::moveSpriteVertical() // true for movement, false for none
{
    if(!collDown) // not on ground
    {
        if(collUp && vSpeed < 0) // if headbutting the ceiling
        {
            vSpeed *= -1;
            yPos++; // so it won't get caught in a loop
            return false;
        }
        vSpeed += 0.1; // accelerate
        yPos += vSpeed; // movement
    }
    else
    {
        if(vSpeed >= 0)
        {
            vSpeed = 0.0;
            return false;
        }
        vSpeed += 0.1; // accelerate
        yPos += vSpeed; // movement
    }
}

void GameObject::objectCollisionCheck(GameObject **that, int listSize) // 0 for none, 1 for top, 2 for right, 3 for bottom, 4 for left, 5 for inside
{
    for(int i = 0; that[i] != NULL && i < listSize; i++)
    {
        objectCollisionCheck(that[i]);
    }
}

void GameObject::operator=(GameObject* that)
{
    facingRight = that->facingRight;
    horizontalMovement = that->horizontalMovement;
    verticalMovement = that->verticalMovement;
    xNumSprites = that->xNumSprites;
    yNumSprites = that->yNumSprites;
    spriteWidth = that->spriteWidth;
    spriteHeight = that->spriteHeight;
    vSpeed = that->vSpeed;
    setSprite(that->spriteSheet, xNumSprites, yNumSprites);
    collUp = that->collUp;
    collDown = that->collDown;
    collLeft = that->collLeft;
    collRight = that->collRight;
}
