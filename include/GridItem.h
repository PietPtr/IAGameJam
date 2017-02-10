#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"

using namespace sf;

class GridItem
{
    public:
        GridItem(Vector2i coords);
    protected:
        Vector2i coords;
    private:
};
