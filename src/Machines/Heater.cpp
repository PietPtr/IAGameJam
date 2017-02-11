#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Heater.h"

using namespace sf;

Heater::Heater(Vector2i coords)
{
    this->coords = coords;
}

void Heater::update(Time dt)
{
    if (line != 0) {
        this->power = line->getPower();
    }
}

void Heater::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(120, 120, 120));
    window->draw(switchShape);
}

void Heater::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

}

float Heater::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}

MachineType Heater::getMachineType()
{
    return HEATER;
}
