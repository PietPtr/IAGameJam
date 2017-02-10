#include "Line.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Line::Line(Vector2i coords)
{
    this->coords = coords;
}

void Line::draw(RenderWindow* window)
{
    float offset = 20 - MAX_POWER / 5;
    float thickness = MAX_POWER / 5;
    float powerOffset = 20 - power / 5;
    float powerThickness = power / 5;

    RectangleShape wire;
    RectangleShape powerShape;

    if (orientation == HORIZONTAL)
    {
        wire.setPosition(coords.x * 40, coords.y * 40 + offset);
        wire.setSize(Vector2f(40, thickness * 2));

        powerShape.setPosition(coords.x * 40, coords.y * 40 + powerOffset);
        powerShape.setSize(Vector2f(40, powerThickness * 2));
    }
    else if (orientation == VERTICAL)
    {
        wire.setPosition(coords.x * 40 + offset, coords.y * 40);
        wire.setSize(Vector2f(thickness * 2, 40));

        powerShape.setPosition(coords.x * 40 + powerOffset, coords.y * 40);
        powerShape.setSize(Vector2f(powerThickness * 2, 40));
    }

    wire.setFillColor(Color(100, 100, 100));
    powerShape.setFillColor(Color(255, 0, 0));
    window->draw(wire);
    window->draw(powerShape);

}
