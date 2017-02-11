#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Light.h"

using namespace sf;

Light::Light(Vector2i coords)
{
    this->coords = coords;
}

void Light::update(Time dt)
{
    if (line != 0) {
        this->power = line->getPower();
    }
}

void Light::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(255, 255, 0));
    window->draw(switchShape);
}

void Light::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    drawType(window, textures, getMachineType());
    drawPowerStatus(window, textures);
}

float Light::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
