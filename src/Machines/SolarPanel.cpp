#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/SolarPanel.h"
#include "Game.h"

using namespace sf;

SolarPanel::SolarPanel(Vector2i coords)
{
    this->coords = coords;
}

void SolarPanel::update(Time dt)
{
    power = (Game::gameInstance->getSunlight() / 5) * 20;
}

void SolarPanel::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    if (power > 0)
        drawTinyMachine(window, textures, 17);
    else
        drawTinyMachine(window, textures, 18);

    if (broken)
        drawBroken(window, textures);
}

void SolarPanel::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    drawType(window, textures, getMachineType());

    if (power > 0)
        drawLargeMachine(window, textures, 17);
    else
        drawLargeMachine(window, textures, 18);

    if (Game::gameInstance->hasActiveComputer())
    {
        std::string powerInfo = "POWER OUT: " + floatToString(power, 1) + " W";
        drawString(window, powerInfo, Vector2f(502, 233), &textures->at(0), Color(0, 200, 0), 100);
    }
}

float SolarPanel::getPowerForLine(Line* line)
{
    if (broken)
        return 0;
    return power;
}

MachineType SolarPanel::getMachineType()
{
    return SOLARPANEL;
}
