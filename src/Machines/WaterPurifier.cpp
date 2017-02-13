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
    if (line != 0 && !broken) {
        this->power = line->getPower();
    }
}

void WaterPurifier::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    drawTinyMachine(window, textures, 19);

    if (broken)
        drawBroken(window, textures);
}

void WaterPurifier::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
	drawType(window, textures, getMachineType());
    drawPowerStatus(window, textures);
    drawLargeMachine(window, textures, 19);
}

float WaterPurifier::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
