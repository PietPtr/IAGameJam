#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Line::Line(Vector2i coords, std::array<Connection*, 2> connections)
{
    this->coords = coords;
    this->connections = connections;

    if (connections[0]->getCoords().x != coords.x && connections[0]->getCoords().y == coords.y) {
        orientation = HORIZONTAL;
    }
    if (connections[0]->getCoords().y != coords.y && connections[0]->getCoords().x == coords.x) {
        orientation = VERTICAL;
    }
}

void Line::update(Time dt) {
    if (connections[0]->getPowerForLine(this) > 0 &&
        connections[1]->getPowerForLine(this) > 0) {
        // explode
    }
    else
    {
        power = connections[0]->getPowerForLine(this) +
                connections[1]->getPowerForLine(this);
    }
}

void Line::draw(RenderWindow* window)
{
    float offset = 20 - MAX_POWER / 5;
    float thickness = MAX_POWER / 5;
    float powerOffset = 20 - power / 5;
    float powerThickness = power / 5;

    powerThickness = powerThickness < 1 && powerThickness > 0 ? 1 : powerThickness;

    RectangleShape wire;
    RectangleShape powerShape;
    if (orientation == HORIZONTAL)
    {
        wire.setPosition(20 + coords.x * 40, 20 + coords.y * 40 + offset);
        wire.setSize(Vector2f(40, thickness * 2));

        powerShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40 + powerOffset);
        powerShape.setSize(Vector2f(40, powerThickness * 2));
    }
    else if (orientation == VERTICAL)
    {
        wire.setPosition(20 + coords.x * 40 + offset, 20 + coords.y * 40);
        wire.setSize(Vector2f(thickness * 2, 40));

        powerShape.setPosition(20 + coords.x * 40 + powerOffset, 20 + coords.y * 40);
        powerShape.setSize(Vector2f(powerThickness * 2, 40));
    }

    wire.setFillColor(Color(100, 100, 100));
    powerShape.setFillColor(Color(255, 0, 0));
    window->draw(wire);
    window->draw(powerShape);

}
