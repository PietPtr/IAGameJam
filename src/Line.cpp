#pragma once
#include "Line.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Line::Line(Vector2i coords)
{
    this->coords = coords;
}
