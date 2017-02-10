#include <SFML/Graphics.hpp>
#include "Line.h"

using namespace sf;

Line::Line(Vector2i coords)
{
    this->coords = coords;
}

void Line::draw(RenderWindow* window)
{
    RectangleShape wire;
    wire.setPosition(coords.x * 40, coords.y * 40);
}
