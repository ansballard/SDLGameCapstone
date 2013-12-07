#include "gameObject.h"

class GameObjectList
{
private:
    static const int MAX_SIZE = 64;
    GameObject **surfaces;
    int listSize;
    SDL_Texture *image;
    int width;
    int height;
    bool removeObject(int index);
    void findObjectsInRange(int x1, int y1, int x2, int y2);
    int *hitList;
    int hitListSize;

public:
    // CONSTRUCTOR/DESTRUCTOR
    GameObjectList(SDL_Texture *imageParam, int widthParam, int heightParam);
    ~GameObjectList();
    // ADD OBJECTS
    bool addObject(int x, int y);
    bool addHorizontal(int x, int y, int numObjects);
    bool addVertical(int x, int y, int numObjects);
    bool addDiagonalPositive(int x, int y, int numObjects);
    bool addDiagonalNegative(int x, int y, int numObjects);
    bool addSquare(int x, int y, int numObjects);
    // REMOVE OBJECTS
    bool removeObjects(int x1, int y1, int x2, int y2);
    // GETTERS
    GameObject* getObject(int index) {return surfaces[index];}
    int getSize() {return listSize;}
    int getObjectX(int index);
    int getObjectY(int index);
    SDL_Texture* getImage() {return image;}
    GameObject** getList() {return surfaces;}
};
