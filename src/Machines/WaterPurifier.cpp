#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/WaterPurifier.h"

using namespace sf;

WaterPurifier::WaterPurifier(Vector2i coords)
{
    this->coords = coords;
}

void WaterPurifier::update(Time dt)
{
    if (line != 0) {
        this->power = line->getPower();
    }
}

void WaterPurifier::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(50, 50, 255));
    window->draw(switchShape);
}

void WaterPurifier::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    drawPowerStatus(window, textures);
}

float WaterPurifier::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
