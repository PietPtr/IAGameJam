#pragma once
#include "Line.h"
#include <SFML/Graphics.hpp>

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
