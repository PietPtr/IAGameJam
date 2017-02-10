#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Line::Line(Vector2i coords, std::array<Switch*, 2> switches)
{
    this->switches = switches;
    this->coords = coords;

    if (switches[0]->getCoords().x != coords.x && switches[0]->getCoords().y == coords.y) {
        orientation = HORIZONTAL;
    }
    if (switches[0]->getCoords().y != coords.y && switches[0]->getCoords().x == coords.x) {
        orientation = VERTICAL;
    }
}

void Line::update() {
    if (switches[0]->getPowerForLine(this) > 0 &&
        switches[1]->getPowerForLine(this) > 0) {
        // explode
    }
    else
    {
        power = switches[0]->getPowerForLine(this) +
            switches[1]->getPowerForLine(this);
    }


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
