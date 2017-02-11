#include "Line.h"
#include <SFML/Graphics.hpp>
#include "SolarPanel.h"

using namespace sf;

SolarPanel::SolarPanel(Vector2i coords)
{
    this->coords = coords;
}

void SolarPanel::update(Time dt)
{

}

void SolarPanel::draw(RenderWindow* window)
{
    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(20, 20, 150));
    window->draw(switchShape);
}

void Heater::drawSelected(RenderWindow* window)
{

}

float SolarPanel::getPowerForLine(Line* line)
{
    return 10;
}
