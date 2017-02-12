#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/CO2Remover.h"
#include "Connection.h"
#include "Game.h"

using namespace sf;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

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

    drawTinyMachine(window, textures, 11);

    if (broken)
        drawBroken(window, textures);
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

    if (Game::gameInstance->hasActiveComputer())
    {
        std::string removeInfo = "CO2 REMOVAL: " + std::to_string((int)(power * CO2REMOVER_SPEED)) + " PPM PER S";
        drawString(window, removeInfo, Vector2f(502, 244), &textures->at(0), Color(0, 200, 0), 100);
    }

    drawLargeMachine(window, textures, 11);
}

float CO2Remover::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
