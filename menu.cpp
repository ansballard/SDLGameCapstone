#include <SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*
* log errors
* @param os output stream
* @param msg error message to write
*/
void logSDLerror(ostream &os, const string &msg)
{
    os << msg << " error: " << SDL_GETError() << endl;
}

/*
* loads bmp into texture rendering device
* @param file bmp file
* @param ren the renderer to load the texture on
* @return  loaded texture, or *null if there are errors
*/
SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren)
{
    // init to null
    SDL_Texture *texture = nullptr;
    // load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    // if load worked, convert and return the texture
    if(loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        // check conversion
        if(texture == nullptr)
        {
            logSDLerror(cout, "CreateTextureFromSurface");
        }
    }
    else
        logSDLerror(cout, "LoadBMP");

    return texture;
}

/*
* draw an sdl_texture to an sdl_renderer at x,y preserving width and height
* @param tex source texture
* @param ren renderer to draw to
* @param x the X coord to draw to
* @param y the Y coord to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
    // setup the rectangle
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    // query texture to get width and height
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(ren, tex, NULL, &dest);
}

if()
