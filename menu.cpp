#include <iostream>
#include <string>
#include "player.h"
#include "gameObjectList.h"
#include "npc.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// CONSTANT FOR LEVEL GAP
/////////////////////////
const int LEVEL_GAP = 96;

// ERROR CHECKING/LOGGING
/////////////////////////
void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void logSDLError(const std::string &msg)
{
    std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

// IMAGE LOADING
////////////////
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if(texture == NULL)
        logSDLError("LoadTexture()");
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dest, SDL_Rect *clip = NULL)
{
    SDL_RenderCopy(ren, tex, clip, &dest);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = NULL)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    if(clip != NULL)
    {
        dest.w = clip->w;
        dest.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    renderTexture(tex, ren, dest, clip);
}

/*

END OF FUNCTIONS, START OF MAIN()

*/

int main(int argc, char **argv)
{
    // INIT SDL
    ///////////
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError("SDL_Init()");
        return 1;
    }

    // INIT IMG
    ///////////
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError("IMG_Init()");
        return 1;
    }

    // INIT WINDOW
    //////////////
    SDL_Window *window = SDL_CreateWindow("Sweg", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
	SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        logSDLError("CreateWindow");
        return 2;
    }

    // INIT RENDERER
    ////////////////
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        logSDLError("CreateRenderer");
        return 3;
    }

    // LOAD SPRITE
    ///////////////////////
    SDL_Texture *p1Image = loadTexture("sprites/knight/knightLeftRight.png", renderer);
    SDL_Texture *backgroundImage = loadTexture("images/backgroundNew.jpg", renderer);
    SDL_Texture *boxImage = loadTexture("images/block.jpg", renderer);
    SDL_Texture *goalImage = loadTexture("images/goal.png", renderer);

    if(p1Image == NULL || backgroundImage == NULL || boxImage == NULL || goalImage == NULL)
    {
        return 4;
    }

    // VARIABLES FOR FPS, KEYS AND PLAYER OBJECTS
    /////////////////////////////////////////////
    SDL_Event e;
    bool quit = false;
    bool aDown = false;
    bool dDown = false;
    bool spaceDown = false;
    int tempX = 0; // for testing tab-delte of objects

    // SPRITE SURFACE ARRAY
    ///////////////////////
    GameObjectList surfaceList = GameObjectList(boxImage, 24, 24);

    surfaceList.addHorizontal(0, SCREEN_HEIGHT - 24, 27);
    surfaceList.addHorizontal(0, SCREEN_HEIGHT - 24 - LEVEL_GAP, 5);
    surfaceList.addHorizontal(24*10, SCREEN_HEIGHT - 24 - LEVEL_GAP*2, 8);
    surfaceList.addHorizontal(24*15, SCREEN_HEIGHT - 24 - LEVEL_GAP*3, 5);
    surfaceList.addHorizontal(24*20, SCREEN_HEIGHT - 24 - LEVEL_GAP*4, 7);

    GameObject *goal = new GameObject(goalImage, SCREEN_WIDTH - 96, 32, 64, 32);

    // PLAYER 1 SPRITE
    //////////////////
    Player *p1 = new Player(true, 0, 0, 32, SCREEN_HEIGHT - 64, 3, 3); // ignore magic numbers, they are magical
    p1->setSprite(p1Image, 2, 2, 32, 32); // see above

    // GAME LOOP
    ////////////
    while(!quit)
    {
        p1->objectCollisionCheck(surfaceList.getList(), surfaceList.getSize());

        // EVENT CATCH LOOP
        ///////////////////
        while(SDL_PollEvent(&e))
        {
            SDL_PumpEvents(); // clear old events?
            if(e.type == SDL_QUIT)
                quit = true;

            // KEY DOWN CHECK
            /////////////////
            else if(e.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = e.key.keysym.sym;
                if(key == SDLK_a || key == SDLK_LEFT) // if 'a' is pressed, you're moving left, facing left, and 'a' is down
                {
                    p1->setHorizontalMovement(-1);
                    aDown = true;
                }
                if(key == SDLK_d || key == SDLK_RIGHT) // if 'd' is pressed, you're moving right, facing right, and 'd' is down
                {
                    p1->setHorizontalMovement(1);
                    dDown = true;
                }
                if(key == SDLK_SPACE && spaceDown == false) // if space pressed
                {
                    spaceDown = true;
                    p1->playerJump();
                }
                if(key == SDLK_q) // q to quit
                    quit = true;
            }

            // KEY UP CHECK
            ///////////////
            else if(e.type == SDL_KEYUP)
            {
                SDL_Keycode key = e.key.keysym.sym;
                if(key == SDLK_a || key == SDLK_LEFT) // if 'a' is released
                {
                    aDown = false;
                    if(!dDown) // if 'd' is not down, stop moving
                        p1->setHorizontalMovement(0);
                    else
                        p1->setHorizontalMovement(1);
                }
                if(key == SDLK_d || key == SDLK_RIGHT) // if 'd' is released
                {
                    dDown = false;
                    if(!aDown) // if 'a' is not down, stop moving
                        p1->setHorizontalMovement(0);
                    else
                        p1->setHorizontalMovement(-1);
                }
                if(key == SDLK_SPACE)
                {
                    spaceDown = false;
                }
                if(key == SDLK_TAB)
                {
                    bool temp = surfaceList.removeObjects(0,0,tempX,640);
                    tempX+=24;
                }
            }
        }

        // UPDATE ANIMATION AND MOVEMENT
        ////////////////////////////////
        p1->moveSprite(SDL_GetTicks());


        p1->clearCollision(); // allows for multiple object collision checking

        // IMAGE RENDERING
        //////////////////
        SDL_RenderClear(renderer);
        renderTexture(backgroundImage, renderer, 0, 0);
        for(int i = 0; i < surfaceList.getSize(); i++)
            renderTexture(surfaceList.getImage(), renderer, surfaceList.getObjectX(i), surfaceList.getObjectY(i));
        renderTexture(goalImage, renderer, goal->getXPos(), goal->getYPos());
        renderTexture(p1->getImage(), renderer, p1->getXPos(), p1->getYPos(), p1->getSprite());
        SDL_RenderPresent(renderer);

        if(p1->objectCollisionCheck(goal) != 0)
        {
            quit = true;
            std::cout << "Such skill, much win, wow\n";
        }

    }

    // RELEASE ALL THE MEMORIES
    ///////////////////////////
    SDL_DestroyTexture(p1Image);
    SDL_DestroyTexture(backgroundImage);
    SDL_DestroyTexture(boxImage);
    SDL_DestroyTexture(goalImage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    delete p1;
    delete p1Image;
    delete boxImage;
    delete goal;
    delete goalImage;

    // NO RUNTIME ERROR SWAG
    ////////////////////////
    return 0;
}
