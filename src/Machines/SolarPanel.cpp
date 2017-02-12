#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/SolarPanel.h"

using namespace sf;

SolarPanel::SolarPanel(Vector2i coords)
{
    this->coords = coords;
}

void SolarPanel::update(Time dt)
{

}

void SolarPanel::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    drawTinyMachine(window, textures, 17);

    if (broken)
        drawBroken(window, textures);
}

void SolarPanel::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

    drawType(window, textures, getMachineType());
    drawLargeMachine(window, textures, 17);
}

float SolarPanel::getPowerForLine(Line* line)
{
    if (broken)
        return 0;
    return 10;
}

MachineType SolarPanel::getMachineType()
{
    return SOLARPANEL;
}
