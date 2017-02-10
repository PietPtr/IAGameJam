#include <SFML/Graphics.hpp>
#include "GridItem.h"

using namespace sf;

GridItem::GridItem(Vector2i coords)
{
    this->coords = coords;
}
