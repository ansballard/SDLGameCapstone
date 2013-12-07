#include "gameObjectList.h"

GameObjectList::GameObjectList(SDL_Texture *imageParam, int widthParam, int heightParam)
{
    listSize = 0;
    surfaces = new GameObject*[MAX_SIZE];
    image = imageParam;
    width = widthParam;
    height = heightParam;
    hitListSize = 0;
}

GameObjectList::~GameObjectList()
{
    for(int i = listSize; i > 0; i--)
    {
        delete surfaces[i];
        surfaces[i] = NULL;
    }
    delete []surfaces;
    surfaces = NULL;
}

bool GameObjectList::addObject(int x, int y)
{
    if(listSize < MAX_SIZE)
    {
        surfaces[listSize] = new GameObject(image, x, y, width, height);
        listSize++;
        return true;
    }
    else
        return false;
}

bool GameObjectList::addHorizontal(int x, int y, int numObjects)
{
    bool temp = true;
    for(int i = 0; i < numObjects; i++)
    {
        temp = addObject(x + (i*width),y);
    }
    return temp;
}

bool GameObjectList::addVertical(int x, int y, int numObjects)
{
    bool temp = true;
    for(int i = 0; i < numObjects; i++)
    {
        temp = addObject(x, y + (i*height));
    }
    return temp;
}

int GameObjectList::getObjectX(int index)
{
    if(index < listSize)
    {
        return surfaces[index]->getXPos();
    }
    else
        return -1;
}

int GameObjectList::getObjectY(int index)
{
    if(index < listSize)
    {
        return surfaces[index]->getYPos();
    }
    else
        return -1;
}

bool GameObjectList::addDiagonalPositive(int x, int y, int numObjects)
{
    bool temp = true;
    for(int i = 0; i < numObjects; i++)
    {
        temp = addObject(x + (i*width),y - (i*width));
    }
    return temp;
}

bool GameObjectList::addDiagonalNegative(int x, int y, int numObjects)
{
    bool temp = true;
    for(int i = 0; i < numObjects; i++)
    {
        temp = addObject(x + (i*width),y + (i*width));
    }
    return temp;
}

bool GameObjectList::addSquare(int x, int y, int numObjects)
{
    bool temp = true;
    for(int i = 0; i < numObjects; i++)
    {
        temp = addHorizontal(x,y+(i*width), numObjects);
    }
    return temp;
}

bool GameObjectList::removeObject(int index)
{
    if(index >= listSize || listSize == 0)
    {
        return false;
    }
    else if(listSize-1 == index)
    {
        listSize--;
        if(listSize != 0)
        {
            delete surfaces[listSize];
            surfaces[listSize] = NULL;
        }
        else
        {
            surfaces[0] = NULL;
        }
        return true;
    }
    else
    {
        listSize--;
        surfaces[index]->copyAll(surfaces[listSize]);
        delete surfaces[listSize];
        surfaces[listSize] = NULL;
        return true;
    }
}

void GameObjectList::findObjectsInRange(int x1, int y1, int x2, int y2)
{
    hitList = new int[listSize];
    for(int i = 0; i < listSize; i++)
    {
        if(surfaces[i]->getXPos() >= x1 && surfaces[i]->getXPos() <= x2 && surfaces[i]->getYPos() >= y1 && surfaces[i]->getYPos() <= y2)
        {
            hitList[hitListSize] = i;
            hitListSize++;
        }
    }
}

bool GameObjectList::removeObjects(int x1, int y1, int x2, int y2)
{
    findObjectsInRange(x1, y1, x2, y2);
    for(int i = hitListSize-1; i >= 0; i--)
    {
        removeObject(hitList[i]);
    }
    delete []hitList;
    hitList = NULL;
    hitListSize = 0;
    return true;
}
