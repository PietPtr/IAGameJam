#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/CO2Remover.h"
#include "Connection.h"

using namespace sf;


CO2Remover::CO2Remover(Vector2i coords)
{
    this->coords = coords;
}

void CO2Remover::update(Time dt)
{
    //this->power = line->getPower();
    if (line != 0) {
        this->power = line->getPower();
    }
}

void CO2Remover::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(10, 10, 10));
    window->draw(switchShape);
}

void CO2Remover::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    Sprite co2Sprite;
    co2Sprite.setTexture(textures->at(2));
    co2Sprite.setPosition(Vector2f(500, 20));
    co2Sprite.setColor(Color(0, 0, 0));
    window->draw(co2Sprite);

    drawType(window, textures, getMachineType());

    drawPowerStatus(window, textures);
}

float CO2Remover::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
