#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Heater.h"

using namespace sf;

Heater::Heater(Vector2i coords)
{
    this->coords = coords;
}

void Heater::setLine(Line * line)
{
    this->line = line;
}

void Heater::update(Time dt)
{

}

void Heater::draw(RenderWindow* window)
{
    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(coords.x * 40, coords.y * 40);
    switchShape.setFillColor(Color(100, 100, 100));
    window->draw(switchShape);
}

float Heater::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
